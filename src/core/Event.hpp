#ifndef CHAKRA_EVENT_HPP
#define CHAKRA_EVENT_HPP

#include "core/EventTypes.hpp"

namespace Chakra
{
    class Event
    {
        public:
            bool m_Handled;

            Event(EventType type);

            EventType   getType();

        private:
            EventType m_Type;
    };
}

#endif
