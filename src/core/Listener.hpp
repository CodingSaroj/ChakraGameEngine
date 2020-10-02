#ifndef CHAKRA_CORE_LISTENER_HPP
#define CHAKRA_CORE_LISTENER_HPP

#include "core/Event.hpp"

namespace Chakra
{
    class Listener
    {
    public:
        virtual ~Listener() = default;

        virtual void OnAttach() {}
        virtual void OnDetach() {}

        virtual bool OnEvent(Event * e) = 0;
    };
}

#endif
