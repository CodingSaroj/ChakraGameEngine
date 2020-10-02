#ifndef CHAKRA_CORE_EVENT_HPP
#define CHAKRA_CORE_EVENT_HPP

#include "core/Common.hpp"

#include "core/EventTypes.hpp"

namespace Chakra
{
    class Event
    {
        public:
            explicit Event(EventType type);

            constexpr bool &    Handled() { return m_Handled; }
            constexpr EventType Type()    { return m_Type; }

        private:
            EventType m_Type;
            bool      m_Handled;
    };
}

#endif
