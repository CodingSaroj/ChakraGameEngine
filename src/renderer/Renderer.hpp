#ifndef CHAKRA_RENDERER_RENDERER_HPP
#define CHAKRA_RENDERER_RENDERER_HPP

#include "core/Common.hpp"

#include "renderer/IRenderer.hpp"

#if CHK_GRAPHICS_API == OpenGL4
    #include "platform/renderer/OpenGL4Renderer.hpp"
#endif

namespace Chakra
{
    class Renderer : public IRenderer
    {
    public:
        Renderer();
        ~Renderer();

        void SetCameraData(glm::mat4 projectionMatrix, glm::mat4 viewMatrix) override;
        void Submit(RenderMesh & mesh, Shader & shader, glm::mat4 transformationMatrix, const std::vector<Texture *> & textures, const std::string & uniformName, std::vector<uint8_t> & data) override;
        void Flush(glm::vec4 clearColor) override;

    private:
        IRenderer * m_Renderer;
    };
}

#endif
