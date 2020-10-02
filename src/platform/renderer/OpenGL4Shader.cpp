#include "OpenGL4Shader.hpp"

namespace Chakra
{
    void OpenGL4Shader::CollectReflectionData(spirv_cross::CompilerGLSL & compiler)
    {
        auto resources = compiler.get_shader_resources();

        for (auto & uniform : resources.uniform_buffers)
        {
            UniformFormat format;
            format.Type = compiler.get_type(uniform.type_id);
            format.Name = uniform.name;
            format.Size = compiler.get_declared_struct_size(format.Type);

            if (format.Type.basetype == spirv_cross::SPIRType::BaseType::Struct)
            {
                for (uint32_t i = 0; ; i++)
                {
                    if (compiler.get_member_name(uniform.base_type_id, i) == "")
                    {
                        break;
                    }

                    format.Members.emplace_back(UniformFormat
                    {
                        compiler.get_type(compiler.get_type(uniform.base_type_id).member_types[i]),
                        compiler.get_member_name(uniform.base_type_id, i),
                        compiler.get_declared_struct_member_size(compiler.get_type(uniform.base_type_id), i)
                    });
                }
            }

            m_UniformFormats.emplace_back(format);
        }

        for (auto & sampledImage : resources.sampled_images)
        {
            UniformFormat format;
            format.Type = compiler.get_type(sampledImage.type_id);
            format.Name = sampledImage.name;
            format.Size = 0;

            m_UniformFormats.emplace_back(format);
        }
    }

    void OpenGL4Shader::Load(std::array<std::vector<uint32_t>, 6> spirvBinaries)
    {
        GLuint vert, tesc, tese, geom, frag, comp;

        GLint success;
        GLchar log[256];

        m_ProgramHandle = CHK_GL_CALL(glCreateProgram());

        if (!spirvBinaries[0].empty())
        {
            spirv_cross::CompilerGLSL compiler(std::move(spirvBinaries[0]));

            CollectReflectionData(compiler);
            
            spirv_cross::CompilerGLSL::Options options;
            options.vulkan_semantics = false;
            options.separate_shader_objects = true;
            options.version = 450;

            compiler.set_common_options(options);

            std::string vertShader = compiler.compile();

            vert = CHK_GL_CALL(glCreateShader(GL_VERTEX_SHADER));

            const char * vertCStr = vertShader.c_str();

            CHK_GL_CALL(glShaderSource(vert, 1, &vertCStr, nullptr));
            CHK_GL_CALL(glCompileShader(vert));

            CHK_GL_CALL(glGetShaderiv(vert, GL_COMPILE_STATUS, &success));

            if (!success)
            {
                CHK_GL_CALL(glGetShaderInfoLog(vert, 256, nullptr, log));
                CHK_ERROR("Renderer::OpenGL4", "Unable to compile vertex shader.\n", log);
            }

            CHK_GL_CALL(glAttachShader(m_ProgramHandle, vert));
        }

        if (!spirvBinaries[1].empty())
        {
            spirv_cross::CompilerGLSL compiler(std::move(spirvBinaries[4]));
            
            CollectReflectionData(compiler);

            spirv_cross::CompilerGLSL::Options options;
            options.vulkan_semantics = false;
            options.separate_shader_objects = true;
            options.version = 450;

            compiler.set_common_options(options);

            std::string tescShader = compiler.compile();

            tesc = CHK_GL_CALL(glCreateShader(GL_TESS_CONTROL_SHADER));

            const char * tescCStr = tescShader.c_str();

            CHK_GL_CALL(glShaderSource(tesc, 1, &tescCStr, nullptr));
            CHK_GL_CALL(glCompileShader(tesc));

            CHK_GL_CALL(glGetShaderiv(tesc, GL_COMPILE_STATUS, &success));

            if (!success)
            {
                CHK_GL_CALL(glGetShaderInfoLog(frag, 256, nullptr, log));
                CHK_ERROR("Renderer::OpenGL4", "Unable to compile tessellation control shader.\n", log);
            }
        
            CHK_GL_CALL(glAttachShader(m_ProgramHandle, tesc));
        }

        if (!spirvBinaries[2].empty())
        {
            spirv_cross::CompilerGLSL compiler(std::move(spirvBinaries[4]));
            
            CollectReflectionData(compiler);

            spirv_cross::CompilerGLSL::Options options;
            options.vulkan_semantics = false;
            options.separate_shader_objects = true;
            options.version = 450;

            compiler.set_common_options(options);

            std::string teseShader = compiler.compile();

            tese = CHK_GL_CALL(glCreateShader(GL_TESS_EVALUATION_SHADER));

            const char * teseCStr = teseShader.c_str();

            CHK_GL_CALL(glShaderSource(tese, 1, &teseCStr, nullptr));
            CHK_GL_CALL(glCompileShader(tese));

            CHK_GL_CALL(glGetShaderiv(tese, GL_COMPILE_STATUS, &success));

            if (!success)
            {
                CHK_GL_CALL(glGetShaderInfoLog(frag, 256, nullptr, log));
                CHK_ERROR("Renderer::OpenGL4", "Unable to compile tessellation evaluation shader.\n", log);
            }
        
            CHK_GL_CALL(glAttachShader(m_ProgramHandle, tese));
        }

        if (!spirvBinaries[3].empty())
        {
            spirv_cross::CompilerGLSL compiler(std::move(spirvBinaries[3]));
            
            CollectReflectionData(compiler);

            spirv_cross::CompilerGLSL::Options options;
            options.vulkan_semantics = false;
            options.separate_shader_objects = true;
            options.version = 450;

            compiler.set_common_options(options);

            std::string geomShader = compiler.compile();

            geom = CHK_GL_CALL(glCreateShader(GL_GEOMETRY_SHADER));

            const char * geomCStr = geomShader.c_str();

            CHK_GL_CALL(glShaderSource(geom, 1, &geomCStr, nullptr));
            CHK_GL_CALL(glCompileShader(geom));

            CHK_GL_CALL(glGetShaderiv(geom, GL_COMPILE_STATUS, &success));

            if (!success)
            {
                CHK_GL_CALL(glGetShaderInfoLog(geom, 256, nullptr, log));
                CHK_ERROR("Renderer::OpenGL4", "Unable to compile geometry shader.\n", log);
            }
            
            CHK_GL_CALL(glAttachShader(m_ProgramHandle, geom));
        }

        if (!spirvBinaries[4].empty())
        {
            spirv_cross::CompilerGLSL compiler(std::move(spirvBinaries[4]));
            
            CollectReflectionData(compiler);

            spirv_cross::CompilerGLSL::Options options;
            options.vulkan_semantics = false;
            options.separate_shader_objects = true;
            options.version = 450;

            compiler.set_common_options(options);

            std::string fragShader = compiler.compile();

            frag = CHK_GL_CALL(glCreateShader(GL_FRAGMENT_SHADER));

            const char * fragCStr = fragShader.c_str();

            CHK_GL_CALL(glShaderSource(frag, 1, &fragCStr, nullptr));
            CHK_GL_CALL(glCompileShader(frag));

            CHK_GL_CALL(glGetShaderiv(frag, GL_COMPILE_STATUS, &success));

            if (!success)
            {
                CHK_GL_CALL(glGetShaderInfoLog(frag, 256, nullptr, log));
                CHK_ERROR("Renderer::OpenGL4", "Unable to compile fragment shader.\n", log);
            }
        
            CHK_GL_CALL(glAttachShader(m_ProgramHandle, frag));
        }

        if (!spirvBinaries[5].empty())
        {
            spirv_cross::CompilerGLSL compiler(std::move(spirvBinaries[3]));
            
            CollectReflectionData(compiler);

            spirv_cross::CompilerGLSL::Options options;
            options.vulkan_semantics = false;
            options.separate_shader_objects = true;
            options.version = 450;

            compiler.set_common_options(options);

            std::string compShader = compiler.compile();

            comp = CHK_GL_CALL(glCreateShader(GL_COMPUTE_SHADER));

            const char * compCStr = compShader.c_str();

            CHK_GL_CALL(glShaderSource(comp, 1, &compCStr, nullptr));
            CHK_GL_CALL(glCompileShader(comp));

            CHK_GL_CALL(glGetShaderiv(comp, GL_COMPILE_STATUS, &success));

            if (!success)
            {
                CHK_GL_CALL(glGetShaderInfoLog(geom, 256, nullptr, log));
                CHK_ERROR("Renderer::OpenGL4", "Unable to compile compute shader.\n", log);
            }
            
            CHK_GL_CALL(glAttachShader(m_ProgramHandle, comp));
        }

        CHK_GL_CALL(glLinkProgram(m_ProgramHandle));

        CHK_GL_CALL(glGetProgramiv(m_ProgramHandle, GL_LINK_STATUS, &success));

        if (!success)
        {
            CHK_GL_CALL(glGetProgramInfoLog(m_ProgramHandle, 256, nullptr, log));
            CHK_ERROR("Renderer::OpenGL4", "Unable to link shader.\n", log);
        }

        if (!spirvBinaries[0].empty())
        {
            CHK_GL_CALL(glDetachShader(m_ProgramHandle, vert));
        }

        if (!spirvBinaries[1].empty())
        {
            CHK_GL_CALL(glDetachShader(m_ProgramHandle, tesc));
        }

        if (!spirvBinaries[2].empty())
        {
            CHK_GL_CALL(glDetachShader(m_ProgramHandle, tese));
        }

        if (!spirvBinaries[3].empty())
        {
            CHK_GL_CALL(glDetachShader(m_ProgramHandle, geom));
        }

        if (!spirvBinaries[4].empty())
        {
            CHK_GL_CALL(glDetachShader(m_ProgramHandle, frag));
        }

        if (!spirvBinaries[5].empty())
        {
            CHK_GL_CALL(glDetachShader(m_ProgramHandle, comp));
        }
        
        if (!spirvBinaries[0].empty())
        {
            CHK_GL_CALL(glDeleteShader(vert));
        }
        if (!spirvBinaries[1].empty())
        {
            CHK_GL_CALL(glDeleteShader(tesc));
        }
        if (!spirvBinaries[2].empty())
        {
            CHK_GL_CALL(glDeleteShader(tese));
        }
        if (!spirvBinaries[3].empty())
        {
            CHK_GL_CALL(glDeleteShader(geom));
        }
        if (!spirvBinaries[4].empty())
        {
            CHK_GL_CALL(glDeleteShader(frag));
        }
        if (!spirvBinaries[5].empty())
        {
            CHK_GL_CALL(glDeleteShader(comp));
        }
    }

    void OpenGL4Shader::Unload()
    {
        CHK_GL_CALL(glDeleteProgram(m_ProgramHandle));
    }

    void OpenGL4Shader::Use()
    {
        CHK_GL_CALL(glUseProgram(m_ProgramHandle));
    }

    std::vector<UniformFormat> OpenGL4Shader::GetUniformFormats()
    {
        return m_UniformFormats;
    }

    void OpenGL4Shader::BindUniformBlock(const std::string & name, uint64_t bindPoint)
    {
        GLuint blockIndex = CHK_GL_CALL(glGetUniformBlockIndex(m_ProgramHandle, name.c_str()));

        CHK_GL_CALL(glUniformBlockBinding(m_ProgramHandle, blockIndex, bindPoint));
    }

    void OpenGL4Shader::LoadUniformFloat(const std::string & name, float value)
    {
        GLint location = CHK_GL_CALL(glGetUniformLocation(m_ProgramHandle, name.c_str()));
        CHK_GL_CALL(glUniform1f(location, value));
    }

    void OpenGL4Shader::LoadUniformVec2(const std::string & name, glm::vec2 value)
    {
        GLint location = CHK_GL_CALL(glGetUniformLocation(m_ProgramHandle, name.c_str()));
        CHK_GL_CALL(glUniform2fv(location, 1, glm::value_ptr(value)));
    }

    void OpenGL4Shader::LoadUniformVec3(const std::string & name, glm::vec3 value)
    {
        GLint location = CHK_GL_CALL(glGetUniformLocation(m_ProgramHandle, name.c_str()));
        CHK_GL_CALL(glUniform3fv(location, 1, glm::value_ptr(value)));
    }

    void OpenGL4Shader::LoadUniformVec4(const std::string & name, glm::vec4 value)
    {
        GLint location = CHK_GL_CALL(glGetUniformLocation(m_ProgramHandle, name.c_str()));
        CHK_GL_CALL(glUniform4fv(location, 1, glm::value_ptr(value)));
    }

    void OpenGL4Shader::LoadUniformMat2(const std::string & name, glm::mat2 value)
    {
        GLint location = CHK_GL_CALL(glGetUniformLocation(m_ProgramHandle, name.c_str()));
        CHK_GL_CALL(glUniformMatrix2fv(location, 1, GL_FALSE, glm::value_ptr(value)));
    }

    void OpenGL4Shader::LoadUniformMat3(const std::string & name, glm::mat3 value)
    {
        GLint location = CHK_GL_CALL(glGetUniformLocation(m_ProgramHandle, name.c_str()));
        CHK_GL_CALL(glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(value)));
    }

    void OpenGL4Shader::LoadUniformMat4(const std::string & name, glm::mat4 value)
    {
        GLint location = CHK_GL_CALL(glGetUniformLocation(m_ProgramHandle, name.c_str()));
        CHK_GL_CALL(glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value)));
    }
}
