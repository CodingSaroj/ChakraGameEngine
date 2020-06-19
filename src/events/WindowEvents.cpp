#include "WindowEvents.hpp"

namespace Chakra
{
    CloseEvent::CloseEvent()
        : Event(EventType::OnClose)
    {
    }
    
    KeyPressEvent::KeyPressEvent(int key, int modifier)
        : Event(EventType::OnKeyPress), m_Key(key), m_Modifier(modifier)
    {
    }
    
    int KeyPressEvent::getKey()
    {
        return m_Key;
    }
    
    int KeyPressEvent::getModifier()
    {
        return m_Modifier;
    }
    
    KeyReleaseEvent::KeyReleaseEvent(int key, int modifier)
        : Event(EventType::OnKeyRelease), m_Key(key), m_Modifier(modifier)
    {
    }
    
    int KeyReleaseEvent::getKey()
    {
        return m_Key;
    }
    
    int KeyReleaseEvent::getModifier()
    {
        return m_Modifier;
    }
    
    MouseButtonPressEvent::MouseButtonPressEvent(int button, int modifier)
        : Event(EventType::OnMouseButtonPress), m_Button(button), m_Modifier(modifier)
    {
    }
    
    int MouseButtonPressEvent::getButton()
    {
        return m_Button;
    }
    
    int MouseButtonPressEvent::getModifier()
    {
        return m_Modifier;
    }
    
    MouseButtonReleaseEvent::MouseButtonReleaseEvent(int button, int modifier)
        : Event(EventType::OnMouseButtonRelease), m_Button(button), m_Modifier(modifier)
    {
    }
    
    int MouseButtonReleaseEvent::getButton()
    {
        return m_Button;
    }
    
    int MouseButtonReleaseEvent::getModifier()
    {
        return m_Modifier;
    }
    
    ScrollEvent::ScrollEvent(double xOffset, double yOffset)
        : Event(EventType::OnScroll), m_XOffset(xOffset), m_YOffset(yOffset)
    {
    }
    
    double ScrollEvent::getXOffset()
    {
        return m_XOffset;
    }
    
    double ScrollEvent::getYOffset()
    {
        return m_YOffset;
    }
    
    MouseMoveEvent::MouseMoveEvent(double x, double y)
        : Event(EventType::OnMouseMove), m_X(x), m_Y(y)
    {
    }
    
    double MouseMoveEvent::getX()
    {
        return m_X;
    }
    
    double MouseMoveEvent::getY()
    {
        return m_Y;
    }
}
