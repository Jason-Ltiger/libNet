#include "Logger.h"
#include "Timestamp.h"

#include <iostream>


Logger& Logger::instance() 
{ 
    static Logger logger;
    return logger;

}

void Logger::setLogLevel(int level) 
{
    loglevel_ = level;

}

void Logger::log(std::string msg) 
{
    switch (loglevel_)
    {
    case INFO:
        std::cout << "[INFO]";
        break;
    case ERROR:
        std::cout << "[ERROR]";
        break;
    case FATAL:
        std::cout << "[FATAL]";
        break;
    case DEBUG:
        std::cout << "[DEBUG]";
        break;
    default:
        break;
    }
    //打印时间
    std::cout << Timestamp::now().toString() << " : " << msg << std::endl;

}
