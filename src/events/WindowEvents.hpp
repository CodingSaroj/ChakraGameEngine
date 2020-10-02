#ifndef CHAKRA_EVENTS_WINDOW_EVENTS_HPP
#define CHAKRA_EVENTS_WINDOW_EVENTS_HPP

#include "core/Common.hpp"

#include "core/EventTypes.hpp"
#include "core/Event.hpp"

namespace Chakra
{
    class WindowCreateEvent : public Event
    {
    public:
        WindowCreateEvent();
    };

    class WindowDestroyEvent : public Event
    {
    public:
        WindowDestroyEvent();
    };
    
    class WindowResizeEvent : public Event
    {
    public:
        WindowResizeEvent(int width, int height);

        int GetWidth();
        int GetHeight();

    private:
        int m_Width;
        int m_Height;
    };

    class ImGuiRenderEvent : public Event
    {
    public:
        ImGuiRenderEvent();
    };

    class KeyTypeEvent : public Event
    {
    public:
        explicit KeyTypeEvent(unsigned int unicodeChar);

        unsigned int GetUnicodeChar();

    private:
        unsigned int m_UnicodeChar;
    };

    class KeyPressEvent : public Event
    {
    public:
        KeyPressEvent(int key, int modifier);

        int GetKey();
        int GetModifier();

    private:
        int m_Key;
        int m_Modifier;
    };

    class KeyReleaseEvent : public Event
    {
    public:
        KeyReleaseEvent(int key, int modifier);

        int GetKey();
        int GetModifier();

    private:
        int m_Key;
        int m_Modifier;
    };

    class MouseButtonPressEvent : public Event
    {
    public:
        MouseButtonPressEvent(int button, int modifier);

        int GetButton();
        int GetModifier();

    private:
        int m_Button;
        int m_Modifier;
    };

    class MouseButtonReleaseEvent : public Event
    {
    public:
        MouseButtonReleaseEvent(int button, int modifier);

        int GetButton();
        int GetModifier();

    private:
        int m_Button;
        int m_Modifier;
    };

    class ScrollEvent : public Event
    {
    public:
        ScrollEvent(double xOffset, double yOffset);

        double GetXOffset();
        double GetYOffset();

    private:
        double m_XOffset;
        double m_YOffset;
    };

    class MouseMoveEvent : public Event
    {
    public:
        MouseMoveEvent(double x, double y);

        double GetX();
        double GetY();

    private:
        double m_X;
        double m_Y;
    };
}

#endif
