#ifndef CHAKRA_CORE_EVENT_MANAGER_HPP
#define CHAKRA_CORE_EVENT_MANAGER_HPP

#include "core/Common.hpp"

#include "core/Listener.hpp"
#include "core/Event.hpp"

namespace Chakra
{
    class EventManager
    {
    public:
        ~EventManager();

        void Push(Listener * listener);
        void Pop(Listener * listener);

        void Propagate(Event && event);

    private:
        std::vector<Listener *> m_Listeners;
    };
};

#endif
