#include "Renderer.hpp"

namespace Chakra
{
    Renderer::Renderer()
    {
    #if CHK_GRAPHICS_API == OpenGL4
        m_Renderer = new OpenGL4Renderer();
    #endif
    }

    Renderer::~Renderer()
    {
    #if CHK_GRAPHICS_API == OpenGL4
        delete (OpenGL4Renderer *)m_Renderer;
    #endif

    }

    void Renderer::SetCameraData(glm::mat4 projectionMatrix, glm::mat4 viewMatrix)
    {
        m_Renderer->SetCameraData(projectionMatrix, viewMatrix);
    }

    void Renderer::Submit(RenderMesh & mesh, Shader & shader, glm::mat4 transformationMatrix, const std::vector<Texture *> & textures, const std::string & uniformName, std::vector<uint8_t> & uniformData)
    {
        m_Renderer->Submit(mesh, shader, transformationMatrix, textures, uniformName, uniformData);
    }

    void Renderer::Flush(glm::vec4 clearColor)
    {
        m_Renderer->Flush(clearColor);
    }
}
