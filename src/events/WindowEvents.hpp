#ifndef CHAKRA_WINDOW_EVENTS_HPP
#define CHAKRA_WINDOW_EVENTS_HPP

#include "core/Common.hpp"

#include "core/EventTypes.hpp"
#include "core/Event.hpp"

namespace Chakra
{
    class CloseEvent : public Event
    {
        public:
            CloseEvent();
    };

    class KeyPressEvent : public Event
    {
        public:
            KeyPressEvent(int key, int modifier);

            int getKey();
            int getModifier();

        private:
            int m_Key;
            int m_Modifier;
    };

    class KeyReleaseEvent : public Event
    {
        public:
            KeyReleaseEvent(int key, int modifier);

            int getKey();
            int getModifier();

        private:
            int m_Key;
            int m_Modifier;
    };

    class MouseButtonPressEvent : public Event
    {
        public:
            MouseButtonPressEvent(int button, int modifier);

            int getButton();
            int getModifier();

        private:
            int m_Button;
            int m_Modifier;
    };

    class MouseButtonReleaseEvent : public Event
    {
        public:
            MouseButtonReleaseEvent(int button, int modifier);

            int getButton();
            int getModifier();

        private:
            int m_Button;
            int m_Modifier;
    };

    class ScrollEvent : public Event
    {
        public:
            ScrollEvent(double xOffset, double yOffset);

            double getXOffset();
            double getYOffset();

        private:
            double m_XOffset;
            double m_YOffset;
    };

    class MouseMoveEvent : public Event
    {
        public:
            MouseMoveEvent(double x, double y);

            double getX();
            double getY();

        private:
            double m_X;
            double m_Y;
    };
}

#endif
