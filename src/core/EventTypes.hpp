#ifndef CHAKRA_CORE_EVENT_TYPES_HPP
#define CHAKRA_CORE_EVENT_TYPES_HPP

namespace Chakra
{
    enum class EventType
    {
        OnWindowCreate,
        OnWindowDestroy,
        OnWindowResize,

        OnImGuiRender,

        OnKeyType,
        OnKeyPress,
        OnKeyRelease,
        OnMouseButtonPress,
        OnMouseButtonRelease,
        OnScroll,
        OnMouseMove
    };
}

#endif
