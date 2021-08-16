#pragma once

#include "noncopyable.h"
#include "Timestamp.h"

#include <vector>
#include <unordered_map> 


namespace net{
    
class Channel;
class EventLoop;

class Poller : noncopyable
{
public:
    using ChannelList = std::vector<Channel*>;
    using ChannelMap = std::unordered_map<int,Channel*>;
    Poller(EventLoop* loop);
    virtual ~Poller();
public:
    //给所有的IO复用保留统一接口
    virtual Timestamp poll(int timeoutMs, ChannelList *activeChannels) = 0;

    virtual void updateChannel(Channel* channel) = 0;

    virtual void removeChannel(Channel* channel) = 0;

    virtual bool hasChannel(Channel* channel) const ;

    // 通过该接口获取具体的IO复用实现
    static Poller* newDefaultPoller(EventLoop* loop);

protected:
    ChannelMap channels_;

private:
    EventLoop* ownerloop_;

};

}
