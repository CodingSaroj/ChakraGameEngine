#include "Event.hpp"

Chakra::Event::Event(EventType type)
    : m_Handled(false), m_Type(type)
{
}

Chakra::EventType Chakra::Event::getType()
{
    return m_Type;
}
