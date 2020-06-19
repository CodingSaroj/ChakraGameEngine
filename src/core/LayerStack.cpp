#include "LayerStack.hpp"

namespace Chakra
{
    LayerStack::~LayerStack()
    {
        for (Layer * layer : m_Layers)
        {
            layer->OnDetach();
        }
    }
    
    void LayerStack::push(Layer * layer)
    {
        m_Layers.emplace_back(layer);
        layer->OnAttach();
    }
    
    void LayerStack::propagate(Event && event)
    {
        for (Layer * layer : m_Layers)
        {
            if (!event.m_Handled)
            {
                event.m_Handled = layer->OnEvent(&event);
            }
            else
            {
                break;
            }
        }
    }
}
