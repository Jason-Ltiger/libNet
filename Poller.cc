#include "Poller.h"
#include "Channel.h"

using namespace net;

Poller::Poller(EventLoop* loop)
    :ownerloop_(loop)
{
}

Poller::~Poller() = default;

bool Poller::hasChannel(Channel* channel) const
{
    return true;
}