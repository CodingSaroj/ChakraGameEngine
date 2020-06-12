#ifndef CHAKRA_EVENT_TYPES_HPP
#define CHAKRA_EVENT_TYPES_HPP

namespace Chakra
{
    enum class EventType
    {
        OnClose,
        OnKeyPress,
        OnKeyRelease,
        OnMouseButtonPress,
        OnMouseButtonRelease,
        OnScroll,
        OnMouseMove
    };
}

#endif
