#include "WindowEvents.hpp"

namespace Chakra
{
    WindowCreateEvent::WindowCreateEvent()
        : Event(EventType::OnWindowCreate)
    {
    }

    WindowDestroyEvent::WindowDestroyEvent()
        : Event(EventType::OnWindowDestroy)
    {
    }

    WindowResizeEvent::WindowResizeEvent(int width, int height)
        : Event(EventType::OnWindowResize), m_Width(width), m_Height(height)
    {
    }

    int WindowResizeEvent::GetWidth()
    {
        return m_Width;
    }

    int WindowResizeEvent::GetHeight()
    {
        return m_Height;
    }

    ImGuiRenderEvent::ImGuiRenderEvent()
        : Event(EventType::OnImGuiRender)
    {
    }
    
    KeyTypeEvent::KeyTypeEvent(unsigned int unicodeChar)
        : Event(EventType::OnKeyType), m_UnicodeChar(unicodeChar)
    {
    }

    unsigned int KeyTypeEvent::GetUnicodeChar()
    {
        return m_UnicodeChar;
    }

    KeyPressEvent::KeyPressEvent(int key, int modifier)
        : Event(EventType::OnKeyPress), m_Key(key), m_Modifier(modifier)
    {
    }
    
    int KeyPressEvent::GetKey()
    {
        return m_Key;
    }
    
    int KeyPressEvent::GetModifier()
    {
        return m_Modifier;
    }
    
    KeyReleaseEvent::KeyReleaseEvent(int key, int modifier)
        : Event(EventType::OnKeyRelease), m_Key(key), m_Modifier(modifier)
    {
    }
    
    int KeyReleaseEvent::GetKey()
    {
        return m_Key;
    }
    
    int KeyReleaseEvent::GetModifier()
    {
        return m_Modifier;
    }
    
    MouseButtonPressEvent::MouseButtonPressEvent(int button, int modifier)
        : Event(EventType::OnMouseButtonPress), m_Button(button), m_Modifier(modifier)
    {
    }
    
    int MouseButtonPressEvent::GetButton()
    {
        return m_Button;
    }
    
    int MouseButtonPressEvent::GetModifier()
    {
        return m_Modifier;
    }
    
    MouseButtonReleaseEvent::MouseButtonReleaseEvent(int button, int modifier)
        : Event(EventType::OnMouseButtonRelease), m_Button(button), m_Modifier(modifier)
    {
    }
    
    int MouseButtonReleaseEvent::GetButton()
    {
        return m_Button;
    }
    
    int MouseButtonReleaseEvent::GetModifier()
    {
        return m_Modifier;
    }
    
    ScrollEvent::ScrollEvent(double xOffset, double yOffset)
        : Event(EventType::OnScroll), m_XOffset(xOffset), m_YOffset(yOffset)
    {
    }
    
    double ScrollEvent::GetXOffset()
    {
        return m_XOffset;
    }
    
    double ScrollEvent::GetYOffset()
    {
        return m_YOffset;
    }
    
    MouseMoveEvent::MouseMoveEvent(double x, double y)
        : Event(EventType::OnMouseMove), m_X(x), m_Y(y)
    {
    }
    
    double MouseMoveEvent::GetX()
    {
        return m_X;
    }
    
    double MouseMoveEvent::GetY()
    {
        return m_Y;
    }
}
