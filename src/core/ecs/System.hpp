#ifndef CHAKRA_SYSTEM_HPP
#define CHAKRA_SYSTEM_HPP

#include <vector>

namespace Chakra
{
    class System
    {
        public:
            virtual void OnInitialize() = 0;
            virtual void OnUpdate()     = 0;
            virtual void OnExit()       = 0;

        protected:
            System()          = default;
            virtual ~System() = default;
    };
}

#endif
