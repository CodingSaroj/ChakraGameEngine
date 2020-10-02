#ifndef CHAKRA_EDITOR_HPP
#define CHAKRA_EDITOR_HPP

#include "Chakra.hpp"

namespace Chakra
{
    class Editor : public Application
    {
    public:
        Editor();

        void OnCreate() override;
        void OnUpdate() override;
        void OnDestroy() override;
        void OnResize(int width, int height) override;
        void OnImGuiRender() override;

        void RenderMenubar();
        void RenderScene();
        void RenderHierarchy();
        void RenderProperties();
        void RenderLog();
        void RenderProfilerWindow();
        void RenderEditorState();

    private:
        bool m_2D = false;
        int m_CurrentResolution = 0;
        bool m_LogCollapse = false;

        bool m_SceneOpen = true;
        bool m_HierarchyOpen = true;
        bool m_PropertyOpen = true;
        bool m_LogOpen = true;
        bool m_ProfileOpen = true;

        uint64_t m_SceneW = 800, m_SceneH = 600;
        Framebuffer m_SceneFramebuffer;
        Entity m_CameraEntity;
        Entity m_SelectedEntity;

    };
}

#endif
