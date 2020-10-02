#include "OpenGL4Renderer.hpp"

namespace Chakra
{
    void OpenGL4Renderer::SetCameraData(glm::mat4 projectionMatrix, glm::mat4 viewMatrix)
    {
        m_ProjectionMatrix = projectionMatrix;
        m_ViewMatrix = viewMatrix;
    }

    void OpenGL4Renderer::Submit(RenderMesh & mesh, Shader & shader, glm::mat4 transformationMatrix, const std::vector<Texture *> & textures, const std::string & uniformName, std::vector<uint8_t> & uniformData)
    {
        if (std::find(m_UsedShaders.begin(), m_UsedShaders.end(), &shader) == m_UsedShaders.end())
        {
            for (auto & uniformFormat : shader.GetUniformFormats())
            {
                if (uniformFormat.Type.basetype != spirv_cross::SPIRType::BaseType::SampledImage)
                {
                    m_UniformBlocks.CreateUniformBlock(uniformFormat.Name, uniformFormat.Size);
                }
            }

            m_UsedShaders.emplace_back(&shader);
        }

        m_RenderQueue[&shader].emplace_back(RenderObject{&mesh, transformationMatrix, textures, uniformName, uniformData});
    }

    void OpenGL4Renderer::Flush(glm::vec4 clearColor)
    {
        CHK_GL_CALL(glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a));
        CHK_GL_CALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
        CHK_GL_CALL(glEnable(GL_DEPTH_TEST));
        CHK_GL_CALL(glEnable(GL_BLEND));
        CHK_GL_CALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        for (auto & item : m_RenderQueue)
        {
            auto[shader, objects] = item;
            
            shader->Use();

            for (auto & obj : objects)
            {
                // Update renderer uniform blocks
                glm::mat4 mvp = m_ProjectionMatrix * m_ViewMatrix * obj.TransformationMatrix;
                m_UniformBlocks.UpdateUniformBlock("r_MVP", 0, glm::value_ptr(mvp), sizeof(GLfloat) * 16);

                // Update user uniform block
                m_UniformBlocks.UpdateUniformBlock(obj.UniformName, 0, obj.UniformData.data(), obj.UniformData.size());


                GLint textureIndex = 0;
                GLint maxTextures;
                CHK_GL_CALL(glGetIntegerv(GL_MAX_TEXTURE_UNITS, &maxTextures));


                // Bind required uniform blocks to shader.
                for (auto & uniformFormat : shader->GetUniformFormats())
                {
                    if (uniformFormat.Type.basetype == spirv_cross::SPIRType::BaseType::SampledImage)
                    {
                        if (textureIndex < maxTextures)
                        {
                            if (obj.Textures.size() > textureIndex)
                            {
                                obj.Textures[textureIndex]->Use(textureIndex);
                            }

                            textureIndex++;
                        }
                        else
                        {
                            CHK_ERROR("Renderer::OpenGL4", "GPU only supports ", maxTextures, " textures but shader requires more.");
                        }
                    }
                    else
                    {
                        shader->BindUniformBlock(uniformFormat.Name, m_UniformBlocks.GetBindingPoint(uniformFormat.Name));
                    }
                }

                obj.Mesh->Use();

                CHK_GL_CALL(glDrawElements(GL_TRIANGLES, (GLsizei)obj.Mesh->GetVertexCount(), GL_UNSIGNED_INT, (const void *)0));

                CHK_GL_CALL(glBindVertexArray(0));

                CHK_GL_CALL(glBindTexture(GL_TEXTURE_2D, 0));
            }

            CHK_GL_CALL(glUseProgram(0));
        }

        m_RenderQueue.clear();
    }
}
