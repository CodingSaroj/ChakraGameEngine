#ifndef CHAKRA_INPUT_HPP
#define CHAKRA_INPUT_HPP

#include <algorithm>
#include <vector>

#include "core/Layer.hpp"

#include "events/WindowEvents.hpp"

namespace Chakra
{
    class Input : public Layer
    {
        public:
            static bool isModPressed(int mod);
            static bool isModReleased(int mod);
            static bool isKeyPressed(int mod);
            static bool isKeyReleased(int key);
            static bool isMouseButtonPressed(int button);
            static bool isMouseButtonReleased(int button);

            static double getScrollOffsetX();
            static double getScrollOffsetY();
            static double getCursorPosX();
            static double getCursorPosY();

            static void clear();

        private:
            static std::vector<int> m_PressedKeys;
            static std::vector<int> m_ReleasedKeys;
            static std::vector<int> m_PressedMouseButtons;
            static std::vector<int> m_ReleasedMouseButtons;

            static int    m_ModPressed;
            static int    m_ModReleased;

            static double m_CursorPosX;
            static double m_CursorPosY;
            static double m_ScrollOffsetX;
            static double m_ScrollOffsetY;

            void OnAttach()         override;
            bool OnEvent(Event * e) override;
            void OnDetach()         override;
    };
}

#endif
