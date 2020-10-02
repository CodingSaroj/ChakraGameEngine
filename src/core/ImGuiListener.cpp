#include "ImGuiListener.hpp"

#include "core/Application.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include <implot/implot.h>

namespace Chakra
{
    void ImGuiListener::OnAttach()
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImPlot::CreateContext();

        ImGuiIO & io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

        ImGui::StyleColorsDark();

        ImGui_ImplGlfw_InitForOpenGL((GLFWwindow *)Application::GetApplication().GetWindow().GetRaw(), true);
        ImGui_ImplOpenGL3_Init("#version 450 core");
    }

    void ImGuiListener::OnDetach()
    {
        ImPlot::DestroyContext();
        ImGui::DestroyContext();

        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
    }

    bool ImGuiListener::OnEvent(Event * e)
    {
        if (e->Type() == EventType::OnImGuiRender)
        {
            if (m_FrameStart)
            {
                ImGui_ImplOpenGL3_NewFrame();
                ImGui_ImplGlfw_NewFrame();
                ImGui::NewFrame();

                m_FrameStart = false;

                return false;
            }
            else
            {
                ImGui::Render();
                int display_w, display_h;
                glfwGetFramebufferSize((GLFWwindow *)Application::GetApplication().GetWindow().GetRaw(), &display_w, &display_h);
                glViewport(0, 0, display_w, display_h);
                ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

                if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
                {
                    GLFWwindow * backup = glfwGetCurrentContext();
                    ImGui::UpdatePlatformWindows();
                    ImGui::RenderPlatformWindowsDefault();
                    glfwMakeContextCurrent(backup);
                }

                m_FrameStart = true;

                return true;
            }
        }
        else if (e->Type() == EventType::OnKeyPress
                 || e->Type() == EventType::OnKeyRelease
                 || e->Type() == EventType::OnKeyType)
        {
            if (ImGui::GetIO().WantCaptureKeyboard || ImGui::GetIO().WantTextInput)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else if (e->Type() == EventType::OnMouseButtonPress
                 || e->Type() == EventType::OnMouseButtonRelease
                 || e->Type() == EventType::OnMouseMove
                 || e->Type() == EventType::OnScroll)
        {
            if (ImGui::GetIO().WantCaptureMouse)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        return false;
    }
}
