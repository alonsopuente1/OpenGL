/*

logger.hpp

Defines an entirely static Logger class to make it easy to log errors, warnings,
debug info, and info for readability in the console

*/

// header guard
#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <stdio.h>

// A log priority enum to state up to which level to display in console. For example
// if level is Warn, all Logger::Warn, Debug and Info messages will be displayed
// but not Error messages
enum class LogPriority : int
{
    Info  = 0, 
    Debug = 1,
    Warn  = 2, 
    Error = 3
};

namespace 
{
    class Logger
    {
    private:
        static LogPriority m_logPriority;

    public:
        static void SetLogPriority(const LogPriority& priority)
        {
            m_logPriority = priority;
        }

        /// @brief Displays an Error message in console
        /// @param message Message to display. Works like the C function 'printf()'
        /// @param ...args Optional additional variables to output to console
        template<typename... Args>
        static void Error(const char* message, Args... args)
        {
            if(m_logPriority >= LogPriority::Error)
            {
                printf("[ERROR]\t");
                printf(message, args...);
                printf("\n");
            }
        }

        /// @brief Displays a Warn message in console
        /// @param message Message to display. Works like the C function 'printf()'
        /// @param ...args Optional additional variables to output to console
        template<typename... Args>
        static void Warn(const char* message, Args... args)
        {
            if(m_logPriority >= LogPriority::Warn)
            {
                printf("[WARN]\t");
                printf(message, args...);
                printf("\n");
            }
        }
        
        /// @brief Displays a Debug message in console
        /// @param message Message to display. Works like the C function 'printf()'
        /// @param ...args Optional additional variables to output to console
        template<typename... Args>
        static void Debug(const char* message, Args... args)
        {
            if(m_logPriority >= LogPriority::Debug)
            {
                printf("[DEBUG]\t");
                printf(message, args...);
                printf("\n");
            }
        }
        
        /// @brief Displays an Info message in console
        /// @param message Message to display. Works like the C function 'printf()'
        /// @param ...args Optional additional variables to output to console
        template<typename... Args>
        static void Info(const char* message, Args... args)
        {
            if(m_logPriority >= LogPriority::Info)
            {
                printf("[INFO]\t");
                printf(message, args...);
                printf("\n");
            }
        }  
    };

    // Initialises the default log priority to 'Error' so all messages get logged
    LogPriority Logger::m_logPriority = LogPriority::Error;
}

#endif