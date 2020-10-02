#include "Input.hpp"

namespace Chakra
{
    std::vector<int> Input::s_PressedKeys;
    std::vector<int> Input::s_ReleasedKeys;
    std::vector<int> Input::s_PressedMouseButtons;
    std::vector<int> Input::s_ReleasedMouseButtons;
    
    int    Input::s_ModPressed;
    int    Input::s_ModReleased;
    
    double Input::s_CursorPosX;
    double Input::s_CursorPosY;
    double Input::s_ScrollOffsetX;
    double Input::s_ScrollOffsetY;
    
    bool Input::OnEvent(Event * e)
    {
        if (e->Type() == EventType::OnKeyPress)
        {
            KeyPressEvent * kpe = (KeyPressEvent *)e;
            Input::s_PressedKeys.push_back(kpe->GetKey());
            Input::s_ModPressed = kpe->GetModifier();
            return true;
        }
        else if (e->Type() == EventType::OnKeyRelease)
        {
            KeyReleaseEvent * kre = (KeyReleaseEvent *)e;
            Input::s_ReleasedKeys.push_back(kre->GetKey());
            Input::s_ModReleased = kre->GetModifier();
    
            if (std::find(s_PressedKeys.begin(), s_PressedKeys.end(), kre->GetKey()) != s_PressedKeys.end())
            {
                s_PressedKeys.erase(std::find(s_PressedKeys.begin(), s_PressedKeys.end(), kre->GetKey()));
            }
    
            return true;
        } 
        else if (e->Type() == EventType::OnMouseButtonPress)
        {
            MouseButtonPressEvent * mpe = (MouseButtonPressEvent *)e;
            Input::s_PressedMouseButtons.push_back(mpe->GetButton());
            Input::s_ModPressed = mpe->GetModifier();
            return true;
        }
        else if (e->Type() == EventType::OnMouseButtonRelease)
        {
            MouseButtonReleaseEvent * mre = (MouseButtonReleaseEvent *)e;
            Input::s_ReleasedMouseButtons.push_back(mre->GetButton());
            Input::s_ModReleased = mre->GetModifier();
    
            if (std::find(s_PressedMouseButtons.begin(), s_PressedMouseButtons.end(), mre->GetButton()) != s_PressedMouseButtons.end())
            {
                s_PressedMouseButtons.erase(std::find(s_PressedMouseButtons.begin(), s_PressedMouseButtons.end(), mre->GetButton()));
            }
    
            return true;
        }
        else if (e->Type() == EventType::OnScroll)
        {
            ScrollEvent * se = (ScrollEvent *)e;
            Input::s_ScrollOffsetX = se->GetXOffset();
            Input::s_ScrollOffsetY = se->GetYOffset();
            return true;
        }
        else if (e->Type() == EventType::OnMouseMove)
        {
            MouseMoveEvent * me = (MouseMoveEvent *)e;
            Input::s_CursorPosX = me->GetX();
            Input::s_CursorPosY = me->GetY();
            return true;
        }

        return false;
    }
    
    bool Input::IsModPressed(int mod)
    {
        return s_ModPressed == mod;
    }
    
    bool Input::IsModReleased(int mod)
    {
        return s_ModReleased == mod;
    }
    
    bool Input::IsKeyPressed(int key)
    {
        return std::find(s_PressedKeys.begin(), s_PressedKeys.end(), key) != s_PressedKeys.end();
    }
    
    bool Input::IsKeyReleased(int key)
    {
        return std::find(s_ReleasedKeys.begin(), s_ReleasedKeys.end(), key) != s_ReleasedKeys.end();
    }
    
    bool Input::IsMouseButtonPressed(int button)
    {
        return std::find(s_PressedMouseButtons.begin(), s_PressedMouseButtons.end(), button) != s_PressedMouseButtons.end();
    }
    
    bool Input::IsMouseButtonReleased(int button)
    {
        return std::find(s_ReleasedMouseButtons.begin(), s_ReleasedMouseButtons.end(), button) != s_ReleasedMouseButtons.end();
    }
    
    double Input::GetCursorPosX()
    {
        return s_CursorPosX;
    }
    
    double Input::GetCursorPosY()
    {
        return s_CursorPosY;
    }
    
    double Input::GetScrollOffsetX()
    {
        return s_ScrollOffsetX;
    }
    
    double Input::GetScrollOffsetY()
    {
        return s_ScrollOffsetY;
    }
    
    void Input::Clear()
    {
        s_ReleasedKeys.clear();
        s_ReleasedMouseButtons.clear();
    }
}
