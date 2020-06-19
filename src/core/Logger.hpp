#ifndef CHAKRA_LOGGER_HPP
#define CHAKRA_LOGGER_HPP

#include "core/Common.hpp"

namespace Chakra
{
    class Logger
    {
        public:
            static void Initialize  (std::ostream & _out = std::cout);

            static void LogInfo     (const std::string & section, const std::string & message);
            static void LogWarning  (const std::string & section, const std::string & message);
            static void LogError    (const std::string & section, const std::string & message);

        private:
            static bool             initialized;
            static std::ostream *   out;
    };
}

#endif
