#ifndef CHAKRA_RENDERER_SHADER_HPP
#define CHAKRA_RENDERER_SHADER_HPP

#include "core/Common.hpp"

#include "renderer/IShader.hpp"

#if CHK_GRAPHICS_API == OpenGL4
    #include "platform/renderer/OpenGL4Shader.hpp"
#endif

namespace Chakra
{
    class Shader : public IShader
    {
    public:
        Shader();
        ~Shader();

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
        IShader * m_Shader;
    };
}

#endif
