#ifndef CHAKRA_PLATFORM_RENDERER_OPENGL3_SHADER_HPP
#define CHAKRA_PLATFORM_RENDERER_OPENGL3_SHADER_HPP

#include "core/Common.hpp"
#include "core/Logger.hpp"

#include "renderer/IShader.hpp"
#include "renderer/UniformFormat.hpp"

#include "platform/renderer/OpenGL4Common.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <spirv-cross/spirv_glsl.hpp> 

namespace Chakra
{
    class OpenGL4Shader : public IShader
    {
    public:
        void Load(std::array<std::vector<uint32_t>, 6> spirvBinaries) override;
        void Unload() override;

        void Use() override;

        std::vector<UniformFormat> GetUniformFormats() override;

        void BindUniformBlock(const std::string & name, uint64_t bindPoint) override;

        void LoadUniformFloat(const std::string & name, float value) override;
        void LoadUniformVec2(const std::string & name, glm::vec2 value) override;
        void LoadUniformVec3(const std::string & name, glm::vec3 value) override;
        void LoadUniformVec4(const std::string & name, glm::vec4 value) override;
        void LoadUniformMat2(const std::string & name, glm::mat2 value) override;
        void LoadUniformMat3(const std::string & name, glm::mat3 value) override;
        void LoadUniformMat4(const std::string & name, glm::mat4 value) override;

    private:
        GLuint m_ProgramHandle;

        std::vector<UniformFormat> m_UniformFormats;

        void CollectReflectionData(spirv_cross::CompilerGLSL & compiler);
    };
}

#endif
