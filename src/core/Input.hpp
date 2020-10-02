#ifndef CHAKRA_CORE_INPUT_HPP
#define CHAKRA_CORE_INPUT_HPP

#include "core/Common.hpp"

#include "core/Listener.hpp"

#include "events/WindowEvents.hpp"

#include <imgui/imgui.h>

namespace Chakra
{
    class Input : public Listener
    {
    public:
        static bool IsModPressed(int mod);
        static bool IsModReleased(int mod);
        static bool IsKeyPressed(int key);
        static bool IsKeyReleased(int key);
        static bool IsMouseButtonPressed(int button);
        static bool IsMouseButtonReleased(int button);

        static double GetScrollOffsetX();
        static double GetScrollOffsetY();
        static double GetCursorPosX();
        static double GetCursorPosY();

        static void Clear();

    private:
        static std::vector<int> s_PressedKeys;
        static std::vector<int> s_ReleasedKeys;
        static std::vector<int> s_PressedMouseButtons;
        static std::vector<int> s_ReleasedMouseButtons;

        static int    s_ModPressed;
        static int    s_ModReleased;

        static double s_CursorPosX;
        static double s_CursorPosY;
        static double s_ScrollOffsetX;
        static double s_ScrollOffsetY;

        bool OnEvent(Event * e) override;
    };
}

#endif
