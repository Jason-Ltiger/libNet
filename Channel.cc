#include "Channel.h"
#include "EventLoop.h"
#include "Logger.h"

#include <sys/epoll.h>
#include <assert.h>

using namespace  net;

const int Channel::kNoneEvent = 0 ;
const int Channel::kReadEvent = EPOLLIN | EPOLLPRI;
const int Channel::kWriteEvent = EPOLLOUT;

Channel::Channel(EventLoop* loop,int fd)
    :loop_(loop), fd_(fd), events_(0), revents_(0), index_(0), tied_(false)
{
}

Channel::~Channel()
{
}

void Channel::tie(const std::shared_ptr<void>& obj)
{
    tie_ = obj;
    tied_ = true;
}

// 当改变channel所表示fd的events事件后，update 负责更新epoll所对应fd的events
// 通过channel所属的eventloop，调用poller相应的方法，注册fd的event事件
// eventloop 包括 channel与poller，channner通过调用eveentloop 去访问poller
void Channel::update()
{
}

//删除通道
void Channel::remove()
{

}

void Channel::handleEvent(Timestamp receiveTime)
{
    std::shared_ptr<void> guard;
    if(tied_)
    {
        guard = tie_.lock();
        if(guard)
        {
            handleEventWithGuard(receiveTime);
        }
    }
    else
    {
        handleEventWithGuard(receiveTime);
    }
}

//根据channel发生的具体事件，由channel负责调用具体的回调操作。
void Channel::handleEventWithGuard(Timestamp receiveTime)
{
    LOG_INFO("channel handleEvent revents:%d\n" ,events_);
    
    if((revents_ & EPOLLHUP) && !(revents_ & EPOLLIN))
    {
        if(closeCallback_) closeCallback_();
    }

    if(revents_ & EPOLLERR)
    {
        if(errorCallback_) errorCallback_();
    }

    if(revents_ & (EPOLLIN | EPOLLPRI))
    {
        if(readCallback_) readCallback_(receiveTime);
    }

    if(revents_ & EPOLLOUT)
    {
        if(writeCallback_) writeCallback_();
    }
}