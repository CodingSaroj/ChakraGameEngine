#ifndef CHAKRA_PLATFORM_RENDERER_OPENGL4_RENDERER_HPP
#define CHAKRA_PLATFORM_RENDERER_OPENGL4_RENDERER_HPP

#include "core/Common.hpp"
#include "core/Logger.hpp"

#include "renderer/RenderMesh.hpp"
#include "renderer/Shader.hpp"
#include "renderer/UniformBlocks.hpp"
#include "renderer/IRenderer.hpp"

#include "platform/renderer/OpenGL4Common.hpp"

namespace Chakra
{
    class OpenGL4Renderer : public IRenderer
    {
    public:
        void SetCameraData(glm::mat4 projectionMatrix, glm::mat4 viewMatrix) override;
        void Submit(RenderMesh & renderer, Shader & shader, glm::mat4 transformationMatrix, const std::vector<Texture *> & textures, const std::string & uniformName, std::vector<uint8_t> & uniformData) override;
        void Flush(glm::vec4 clearColor) override;

    private:
        struct RenderObject
        {
            RenderMesh *           Mesh;
            glm::mat4              TransformationMatrix;
            std::vector<Texture *> Textures;
            std::string            UniformName;
            std::vector<uint8_t> & UniformData;
        };

        std::unordered_map<Shader *, std::vector<RenderObject>> m_RenderQueue;
        std::vector<Shader *> m_UsedShaders;
        glm::mat4 m_ProjectionMatrix;
        glm::mat4 m_ViewMatrix;

        UniformBlocks m_UniformBlocks;
    };
}

#endif
