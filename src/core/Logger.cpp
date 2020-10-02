#include "Logger.hpp"

namespace Chakra
{
    std::ostream * Logger::s_Out = &std::cout;
    
    void Logger::SetOStream(std::ostream & out)
    {
        s_Out = &out;
    }
}
