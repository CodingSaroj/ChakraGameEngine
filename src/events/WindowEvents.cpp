#include "WindowEvents.hpp"

Chakra::CloseEvent::CloseEvent()
    : Event(EventType::OnClose)
{
}

Chakra::KeyPressEvent::KeyPressEvent(int key, int modifier)
    : Event(EventType::OnKeyPress), m_Key(key), m_Modifier(modifier)
{
}

int Chakra::KeyPressEvent::getKey()
{
    return m_Key;
}

int Chakra::KeyPressEvent::getModifier()
{
    return m_Modifier;
}

Chakra::KeyReleaseEvent::KeyReleaseEvent(int key, int modifier)
    : Event(EventType::OnKeyRelease), m_Key(key), m_Modifier(modifier)
{
}

int Chakra::KeyReleaseEvent::getKey()
{
    return m_Key;
}

int Chakra::KeyReleaseEvent::getModifier()
{
    return m_Modifier;
}

Chakra::MouseButtonPressEvent::MouseButtonPressEvent(int button, int modifier)
    : Event(EventType::OnMouseButtonPress), m_Button(button), m_Modifier(modifier)
{
}

int Chakra::MouseButtonPressEvent::getButton()
{
    return m_Button;
}

int Chakra::MouseButtonPressEvent::getModifier()
{
    return m_Modifier;
}

Chakra::MouseButtonReleaseEvent::MouseButtonReleaseEvent(int button, int modifier)
    : Event(EventType::OnMouseButtonRelease), m_Button(button), m_Modifier(modifier)
{
}

int Chakra::MouseButtonReleaseEvent::getButton()
{
    return m_Button;
}

int Chakra::MouseButtonReleaseEvent::getModifier()
{
    return m_Modifier;
}

Chakra::ScrollEvent::ScrollEvent(double xOffset, double yOffset)
    : Event(EventType::OnScroll), m_XOffset(xOffset), m_YOffset(yOffset)
{
}

double Chakra::ScrollEvent::getXOffset()
{
    return m_XOffset;
}

double Chakra::ScrollEvent::getYOffset()
{
    return m_YOffset;
}

Chakra::MouseMoveEvent::MouseMoveEvent(double x, double y)
    : Event(EventType::OnMouseMove), m_X(x), m_Y(y)
{
}

double Chakra::MouseMoveEvent::getX()
{
    return m_X;
}

double Chakra::MouseMoveEvent::getY()
{
    return m_Y;
}
