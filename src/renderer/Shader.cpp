#include "Shader.hpp"

namespace Chakra
{
    Shader::Shader()
    {
    #if CHK_GRAPHICS_API == OpenGL4
        m_Shader = new OpenGL4Shader();
    #endif
    }

    Shader::~Shader()
    {
    #if CHK_GRAPHICS_API == OpenGL4
        delete (OpenGL4Shader *)m_Shader;
    #endif
    }

    void Shader::Load(std::array<std::vector<uint32_t>, 6> spirvBinaries)
    {
        m_Shader->Load(spirvBinaries);
    }

    void Shader::Unload()
    {
        m_Shader->Unload();
    }

    void Shader::Use()
    {
        m_Shader->Use();
    }
    
    std::vector<UniformFormat> Shader::GetUniformFormats()
    {
        return m_Shader->GetUniformFormats();
    }

    void Shader::BindUniformBlock(const std::string & name, uint64_t bindPoint)
    {
        m_Shader->BindUniformBlock(name, bindPoint);
    }

    void Shader::LoadUniformFloat(const std::string & name, float value)
    {
        m_Shader->LoadUniformFloat(name, value);
    }

    void Shader::LoadUniformVec2(const std::string & name, glm::vec2 value)
    {
        m_Shader->LoadUniformVec2(name, value);
    }

    void Shader::LoadUniformVec3(const std::string & name, glm::vec3 value)
    {
        m_Shader->LoadUniformVec3(name, value);
    }

    void Shader::LoadUniformVec4(const std::string & name, glm::vec4 value)
    {
        m_Shader->LoadUniformVec4(name, value);
    }

    void Shader::LoadUniformMat2(const std::string & name, glm::mat2 value)
    {
        m_Shader->LoadUniformMat2(name, value);
    }

    void Shader::LoadUniformMat3(const std::string & name, glm::mat3 value)
    {
        m_Shader->LoadUniformMat3(name, value);
    }

    void Shader::LoadUniformMat4(const std::string & name, glm::mat4 value)
    {
        m_Shader->LoadUniformMat4(name, value);
    }
}
