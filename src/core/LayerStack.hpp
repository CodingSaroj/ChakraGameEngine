#ifndef CHAKRA_LAYER_STACK_HPP
#define CHAKRA_LAYER_STACK_HPP

#include "core/Common.hpp"

#include "core/Layer.hpp"
#include "core/Event.hpp"

namespace Chakra
{
    class LayerStack
    {
        public:
            ~LayerStack();

            void push(Layer * layer);

            void propagate(Event && event);

        private:
            std::vector<Layer *> m_Layers;
    };
};

#endif
