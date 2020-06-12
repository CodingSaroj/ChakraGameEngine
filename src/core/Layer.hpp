#ifndef CHAKRA_LAYER_HPP
#define CHAKRA_LAYER_HPP

#include "core/Event.hpp"

namespace Chakra
{
    class Layer
    {
        public:
            virtual ~Layer() = default;

            virtual void OnAttach()         = 0;
            virtual bool OnEvent(Event * e) = 0;
            virtual void OnDetach()         = 0;
    };
}

#endif
