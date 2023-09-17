#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <stdio.h>

enum class LogPriority : int
{
    Info = 0, Debug, Warn, Error
};

namespace 
{
    class Logger
    {
    private:
        static LogPriority m_logPriority;

    public:
        static void SetLogPriority(LogPriority priority)
        {
            m_logPriority = priority;
        }

        template<typename... Args>
        static void Error(const char* message, Args... args)
        {
            if(m_logPriority <= LogPriority::Error)
            {
                printf("[ERROR]\t");
                printf(message, args...);
                printf("\n");
            }
        }

        template<typename... Args>
        static void Warn(const char* message, Args... args)
        {
            if(m_logPriority <= LogPriority::Warn)
            {
                printf("[WARN]\t");
                printf(message, args...);
                printf("\n");
            }
        }
        
        template<typename... Args>
        static void Debug(const char* message, Args... args)
        {
            if(m_logPriority <= LogPriority::Debug)
            {
                printf("[DEBUG]\t");
                printf(message, args...);
                printf("\n");
            }
        }
        
        template<typename... Args>
        static void Info(const char* message, Args... args)
        {
            if(m_logPriority <= LogPriority::Info)
            {
                printf("[INFO]\t");
                printf(message, args...);
                printf("\n");
            }
        }  
    };

    LogPriority Logger::m_logPriority = LogPriority::Info;
}

#endif