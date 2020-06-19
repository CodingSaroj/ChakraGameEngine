#include "Event.hpp"

namespace Chakra
{
    Event::Event(EventType type)
        : m_Handled(false), m_Type(type)
    {
    }
    
    EventType Event::getType()
    {
        return m_Type;
    }
}
