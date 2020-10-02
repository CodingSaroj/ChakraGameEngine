#ifndef CHAKRA_RENDERER_ISHADER_HPP
#define CHAKRA_RENDERER_ISHADER_HPP

#include "core/Common.hpp"

#include "renderer/UniformFormat.hpp"

namespace Chakra
{
    class IShader
    {
    public:
        virtual ~IShader() = default;

        virtual void Load(std::array<std::vector<uint32_t>, 6> spirvBinaries) = 0;
        virtual void Unload() = 0;

        virtual void Use() = 0;

        virtual std::vector<UniformFormat> GetUniformFormats() = 0;

        virtual void BindUniformBlock(const std::string & name, uint64_t bindPoint) = 0;

        virtual void LoadUniformFloat(const std::string & name, float value) = 0;
        virtual void LoadUniformVec2(const std::string & name, glm::vec2 value) = 0;
        virtual void LoadUniformVec3(const std::string & name, glm::vec3 value) = 0;
        virtual void LoadUniformVec4(const std::string & name, glm::vec4 value) = 0;
        virtual void LoadUniformMat2(const std::string & name, glm::mat2 value) = 0;
        virtual void LoadUniformMat3(const std::string & name, glm::mat3 value) = 0;
        virtual void LoadUniformMat4(const std::string & name, glm::mat4 value) = 0;
    };
}

#endif
