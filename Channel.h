#pragma once

#include "noncopyable.h"
#include "Timestamp.h"

#include <functional>
#include <memory>

class EventLoop;

namespace net
{

//通道，封装了socketfd、相应的event、callback(EPOLLIN、EPOLLOUT)
//绑定返回具体对应的事件
class Channel : noncopyable
{
public:
    typedef std::function<void()> EventCallback;
    typedef std::function<void(Timestamp)> ReadEventCallback;

    Channel(EventLoop* loop,int fd);
    ~Channel();
public:
    void handleEvent(Timestamp receiveTime);

    //设置回调函数
    void setReadCallback(ReadEventCallback cb) { readCallback_ = std::move(cb); }

    void setWriteCallback(EventCallback cb) { writeCallback_ = std::move(cb); }

    void setCloseCallback(EventCallback cb) { closeCallback_ = std::move(cb); }

    void setErrorCallback(EventCallback cb) { errorCallback_ = std::move(cb); }

    //防止channel被手动move，channel还在执行回调操作
    void tie(const std::shared_ptr<void>& obj);

    int fd() const { return fd_; }

    int set_revents(int revt) { revents_ = revt; }

    bool inNoneEvent() const { return events_ == kNoneEvent; }

    //设置fd对应的事件状态
    void enableReading() { events_ |= kReadEvent; update(); }
    void disableReading() { events_ &= ~kReadEvent; update(); }
    void enableWriting() { events_ |= kWriteEvent; update(); }
    void disableWriting() { events_ &= ~kWriteEvent; update();}
    void disableAll() { events_ = kNoneEvent; update(); }

    bool isNoneEvent() { return events_ == kNoneEvent; } 
    bool isWriting() const { return events_ & kWriteEvent; }
    bool isReading() const { return events_ & kReadEvent; }

    int index() const { return index_; }
    void set_index(int idx) { index_= idx; }

    EventLoop* ownerLoop() { return loop_; }
    void remove() ;

private:
    void update();
    void handleEventWithGuard(Timestamp receiveTime);

private:
    static const int kNoneEvent;
    static const int kReadEvent;
    static const int kWriteEvent;

    EventLoop* loop_;      //事件循环
    const int  fd_;        //监听fd
    int        events_;    //注册感兴趣的事件
    int        revents_;   //返回的事件
    int        index_;
    bool       logHup_;

    std::weak_ptr<void> tie_;
    bool                tied_;
    ReadEventCallback   readCallback_;
    EventCallback       writeCallback_;
    EventCallback       closeCallback_;
    EventCallback       errorCallback_;
     
};

}