#include "LayerStack.hpp"

Chakra::LayerStack::~LayerStack()
{
    for (Layer * layer : m_Layers)
    {
        layer->OnDetach();
    }
}

void Chakra::LayerStack::push(Layer * layer)
{
    m_Layers.emplace_back(layer);
    layer->OnAttach();
}

void Chakra::LayerStack::propagate(Event && event)
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
