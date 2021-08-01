#pragma once

namespace net{

// 派生类对象不可进行拷贝构造、拷贝赋值操作
class noncopyable
{
public:
    noncopyable(const noncopyable&) = delete;
    void operator=(const noncopyable&) = delete;
protected:
    noncopyable() = default;
    ~noncopyable() = default;
};
   
}