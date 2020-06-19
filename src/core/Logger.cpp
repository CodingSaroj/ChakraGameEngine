#include "Logger.hpp"

namespace Chakra
{
    bool             Logger::initialized = false;
    std::ostream *   Logger::out;
    
    void Logger::Initialize(std::ostream & _out)
    {
        initialized = true;
        out         = &_out;
    }
    
    void Logger::LogInfo(const std::string & section, const std::string & message)
    {
        #if CHK_LOG_LEVEL >= 1
            if (!initialized)
            {
                return;
            }
    
            ((std::ostream &)*out)<<"INFO::"<<section<<": "<<message<<".\n";
        #endif
    }
    
    void Logger::LogWarning(const std::string & section, const std::string & message)
    {
        #if CHK_LOG_LEVEL >= 2
            if (!initialized)
            {
                return;
            }
    
            ((std::ostream &)*out)<<"WARNING::"<<section<<": "<<message<<".\n";
        #endif
    }
    
    void Logger::LogError(const std::string & section, const std::string & message)
    {
        #if CHK_LOG_LEVEL == 3
            if (!initialized)
            {
                return;
            }
    
            ((std::ostream &)*out)<<"ERROR::"<<section<<": "<<message<<".\n";
        #endif
    }
}
