#include "Input.hpp"

namespace Chakra
{
    std::vector<int> Input::m_PressedKeys;
    std::vector<int> Input::m_ReleasedKeys;
    std::vector<int> Input::m_PressedMouseButtons;
    std::vector<int> Input::m_ReleasedMouseButtons;
    
    int    Input::m_ModPressed;
    int    Input::m_ModReleased;
    
    double Input::m_CursorPosX;
    double Input::m_CursorPosY;
    double Input::m_ScrollOffsetX;
    double Input::m_ScrollOffsetY;
    
    void Input::OnAttach()
    {
    }
    
    bool Input::OnEvent(Event * e)
    {
        if (e->getType() == EventType::OnKeyPress)
        {
            KeyPressEvent * kpe = (KeyPressEvent *)e;
            Input::m_PressedKeys.push_back(kpe->getKey());
            Input::m_ModPressed = kpe->getModifier();
            return true;
        }
        else if (e->getType() == EventType::OnKeyRelease)
        {
            KeyReleaseEvent * kre = (KeyReleaseEvent *)e;
            Input::m_ReleasedKeys.push_back(kre->getKey());
            Input::m_ModReleased = kre->getModifier();
    
            m_PressedKeys.erase(std::find(m_PressedKeys.begin(), m_PressedKeys.end(), kre->getKey()));
    
            return true;
        }
        else if (e->getType() == EventType::OnMouseButtonPress)
        {
            MouseButtonPressEvent * mpe = (MouseButtonPressEvent *)e;
            Input::m_PressedMouseButtons.push_back(mpe->getButton());
            Input::m_ModPressed = mpe->getModifier();
            return true;
        }
        else if (e->getType() == EventType::OnMouseButtonRelease)
        {
            MouseButtonReleaseEvent * mre = (MouseButtonReleaseEvent *)e;
            Input::m_ReleasedMouseButtons.push_back(mre->getButton());
            Input::m_ModReleased = mre->getModifier();
    
            m_PressedMouseButtons.erase(std::find(m_PressedMouseButtons.begin(), m_PressedMouseButtons.end(), mre->getButton()));
    
            return true;
        }
        else if (e->getType() == EventType::OnScroll)
        {
            ScrollEvent * se = (ScrollEvent *)e;
            Input::m_ScrollOffsetX = se->getXOffset();
            Input::m_ScrollOffsetY = se->getYOffset();
            return true;
        }
        else if (e->getType() == EventType::OnMouseMove)
        {
            MouseMoveEvent * me = (MouseMoveEvent *)e;
            Input::m_CursorPosX = me->getX();
            Input::m_CursorPosY = me->getY();
            return true;
        }
        else
        {
            return false;
        }
    }
    
    void Input::OnDetach()
    {
    }
    
    bool Input::isModPressed(int mod)
    {
        return m_ModPressed == mod;
    }
    
    bool Input::isModReleased(int mod)
    {
        return m_ModReleased == mod;
    }
    
    bool Input::isKeyPressed(int key)
    {
        return std::find(m_PressedKeys.begin(), m_PressedKeys.end(), key) != m_PressedKeys.end();
    }
    
    bool Input::isKeyReleased(int key)
    {
        return std::find(m_ReleasedKeys.begin(), m_ReleasedKeys.end(), key) != m_ReleasedKeys.end();
    }
    
    bool Input::isMouseButtonPressed(int button)
    {
        return std::find(m_PressedMouseButtons.begin(), m_PressedMouseButtons.end(), button) != m_PressedMouseButtons.end();
    }
    
    bool Input::isMouseButtonReleased(int button)
    {
        return std::find(m_ReleasedMouseButtons.begin(), m_ReleasedMouseButtons.end(), button) != m_ReleasedMouseButtons.end();
    }
    
    double Input::getCursorPosX()
    {
        return m_CursorPosX;
    }
    
    double Input::getCursorPosY()
    {
        return m_CursorPosY;
    }
    
    double Input::getScrollOffsetX()
    {
        return m_ScrollOffsetX;
    }
    
    double Input::getScrollOffsetY()
    {
        return m_ScrollOffsetY;
    }
    
    void Input::clear()
    {
        m_ReleasedKeys.clear();
        m_ReleasedMouseButtons.clear();
    }
}
