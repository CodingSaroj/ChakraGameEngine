#include "Logger.hpp"

bool             Chakra::Logger::initialized = false;
std::ostream *   Chakra::Logger::out;

void Chakra::Logger::Initialize(std::ostream & _out)
{
    initialized = true;
    out         = &_out;
}

void Chakra::Logger::LogInfo(const std::string & section, const std::string & message)
{
    #if CHK_LOG_LEVEL >= 1
        if (!initialized)
        {
            return;
        }

        ((std::ostream &)*out)<<"INFO::"<<section<<": "<<message<<".\n";
    #endif
}

void Chakra::Logger::LogWarning(const std::string & section, const std::string & message)
{
    #if CHK_LOG_LEVEL >= 2
        if (!initialized)
        {
            return;
        }

        ((std::ostream &)*out)<<"WARNING::"<<section<<": "<<message<<".\n";
    #endif
}

void Chakra::Logger::LogError(const std::string & section, const std::string & message)
{
    #if CHK_LOG_LEVEL == 4
        if (!initialized)
        {
            return;
        }

        ((std::ostream &)*out)<<"ERROR::"<<section<<": "<<message<<".\n";
    #endif
}
