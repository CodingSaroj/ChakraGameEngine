#ifndef CHAKRA_CORE_IMGUI_LAYER_HPP
#define CHAKRA_CORE_IMGUI_LAYER_HPP

#include "core/Common.hpp"

#include "core/Listener.hpp"

namespace Chakra
{
    class ImGuiListener : public Listener
    {
    public:
        void OnAttach() override;
        bool OnEvent(Event * e) override;
        void OnDetach() override;

    private:
        bool m_FrameStart = true;
    };
}

#endif
