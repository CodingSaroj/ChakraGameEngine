#include "Event.hpp"

namespace Chakra
{
    Event::Event(EventType type)
        : m_Type(type), m_Handled(false)
    {
    }
}
