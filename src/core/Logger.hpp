#ifndef CHAKRA_CORE_LOGGER_HPP
#define CHAKRA_CORE_LOGGER_HPP

#include "core/Common.hpp"

namespace Chakra
{
    class Logger
    {
    public:
        static void SetOStream(std::ostream & out);

        template <typename... Args>
        static void LogInfo(const std::string & section, Args... args)
        {
            std::ostream & out = *s_Out;

            out<<"Info::"<<section<<": ";
            ((out<<args), ...);
            out<<"\n";
        }

        template <typename... Args>
        static void LogWarning(const std::string & section, Args... args)
        {
            std::ostream & out = *s_Out;

            out<<"Warning::"<<section<<": ";
            ((out<<args), ...);
            out<<"\n";
        }

        template <typename... Args>
        static void LogError(const std::string & section, Args... args)
        {
            std::ostream & out = *s_Out;

            out<<"Error::"<<section<<": ";
            ((out<<args), ...);
            out<<"\n";
        }

        template <typename... Args>
        static void LogFatalError(const std::string & section, Args... args)
        {
            std::cerr<<"Error::"<<section<<": ";
            ((std::cerr<<args), ...);
            std::cerr<<"\n";
        }

    private:
        static std::ostream * s_Out;
    };

    #ifdef DEBUG
        #if CHK_LOG_LEVEL >= 1
            #define CHK_INFO(...) Logger::LogInfo(__VA_ARGS__)
        #endif

        #if CHK_LOG_LEVEL >= 2
            #define CHK_WARNING(...) Logger::LogWarning(__VA_ARGS__)
        #endif

        #if CHK_LOG_LEVEL == 3
            #define CHK_ERROR(...) Logger::LogError(__VA_ARGS__)

            #define CHK_ASSERT(cond, ...) if (!(cond)) { Logger::LogFatalError(__VA_ARGS__); raise(SIGABRT); }
        #endif
    #else
        #define CHK_INFO(...)
        #define CHK_WARNING(...)
        #define CHK_ERROR(...)

        #define CHK_ASSERT(cond, ...)
    #endif
}

#endif
