#include "EventManager.hpp"

namespace Chakra
{
    EventManager::~EventManager()
    {
        for (Listener * listener : m_Listeners)
        {
            listener->OnDetach();
        }
    }
    
    void EventManager::Push(Listener * listener)
    {
        m_Listeners.emplace_back(listener);
        listener->OnAttach();
    }
    
    void EventManager::Propagate(Event && event)
    {
        for (Listener * listener : m_Listeners)
        {
            if (!event.Handled())
            {
                event.Handled() = listener->OnEvent(&event);
            }
            else
            {
                break;
            }
        }
    }
}
