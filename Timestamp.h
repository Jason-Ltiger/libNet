#pragma once

#include <iostream>
#include <string>

class Timestamp
{
public:
    Timestamp();
    ~Timestamp()=default;
    explicit Timestamp(__int64_t micoroSecondsSinceEpoch);
public:
    static Timestamp now();
    std::string toString() const;
static const int kMicroSecondsPerSecond = 1000 * 1000;

private:
   __int64_t micoroSecondsSinceEpoch_;

};