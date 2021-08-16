#include "Poller.h"

#include <stdio.h>

using namespace net; 

Poller* Poller::newDefaultPoller(EventLoop* loop)
{
    if(::getenv("MUDUO_USE_POOL"))
    {
        return nullptr; //生成pool对象。
    }
    else
    {
        return nullptr;  //生成epoll对象。
    }

}