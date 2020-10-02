#ifndef CHAKRA_RENDERER_IRENDERER_HPP
#define CHAKRA_RENDERER_IRENDERER_HPP

#include "core/Common.hpp"

#include "renderer/RenderMesh.hpp"
#include "renderer/Shader.hpp"
#include "renderer/Texture.hpp"

namespace Chakra
{
    class IRenderer
    {
    public:
        virtual ~IRenderer() = default;

        virtual void SetCameraData(glm::mat4 projectionMatrix, glm::mat4 viewMatrix) = 0;
        virtual void Submit(RenderMesh & mesh, Shader & shader, glm::mat4 transformationMatrix, const  std::vector<Texture *> & textures, const std::string & uniformName, std::vector<uint8_t> & uniformData) = 0;
        virtual void Flush(glm::vec4 clearColor) = 0;
    };
}

#endif
