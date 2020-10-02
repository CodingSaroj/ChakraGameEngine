#include "Scene.hpp"

namespace Chakra
{
    Entity Scene::AddEntity(const std::string & tag)
    {
        Entity entity(m_Registry.create(), &m_Registry);
        
        entity.AddComponent<TagComponent>(tag);

        return entity;
    }

    void Scene::RemoveEntity(Entity entity)
    {
        m_Registry.remove(entity.m_Handle);
    }
    
    void Scene::OnCreate()
    {
        {
            auto view = m_Registry.view<NativeScriptComponent>();

            for (auto & entity : view)
            {
                auto & nsc = view.get(entity);

                nsc.CreateInstanceFunction(Entity(entity, &m_Registry), &nsc.ScriptInstance);

                nsc.ScriptInstance->OnCreate();
            }
        }
    }

    void Scene::OnUpdate()
    {
        {
            auto view = m_Registry.view<TransformComponent, CameraComponent>();

            for (auto & entity : view)
            {
                auto[transform, camera] = view.get<TransformComponent, CameraComponent>(entity);

                if (camera.MainCamera)
                {
                    glm::vec3 rotation(glm::eulerAngles(transform.Rotation));
                    glm::vec3 rotDirection(0.0f, 0.0f, -1.0f);

                    rotDirection.x = cos(rotation.x) * cos(rotation.y);
                    rotDirection.y = sin(rotation.y);
                    rotDirection.z = sin(rotation.x) * cos(rotation.y);

                    glm::vec3 position(transform.Transform[3]);
                    glm::vec3 target(glm::normalize(rotDirection));
                    glm::vec3 direction(glm::normalize(position - target));
                    glm::vec3 right(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), direction));
                    glm::vec3 up(glm::cross(direction, right));

                    glm::mat4 viewMatrix = glm::lookAt(position, glm::normalize(target), glm::normalize(up));
                    m_Renderer.SetCameraData(camera.ProjectionMatrix, viewMatrix);
                    break;
                }
            }
        }

        {
            auto view = m_Registry.view<TransformComponent, MaterialComponent>();

            for (auto & entity : view)
            {
                auto[transform, material] = view.get<TransformComponent, MaterialComponent>(entity);

                if (!AssetManager::Get<MeshAsset>(material.Mesh.Key))
                {
                    CHK_ERROR("Scene::OnUpdate", "Invalid AssetReference to MeshAsset with Key `", material.Mesh.Key, "`.");
                    continue;
                }

                if (!AssetManager::Get<ShaderAsset>(material.Shader.Key))
                {
                    CHK_ERROR("Scene::OnUpdate", "Invalid AssetReference to ShaderAsset with Key `", material.Shader.Key, "`.");
                    continue;
                }

                std::vector<Texture *> textures;

                for (auto & textureAssetRef : material.Textures)
                {
                    if (!AssetManager::Get<TextureAsset>(textureAssetRef.Key))
                    {
                        CHK_ERROR("Scene::OnUpdate", "Invalid AssetReference to TextureAsset with Key `", textureAssetRef.Key, "`.");
                        continue;
                    }

                    textures.emplace_back(&AssetManager::Get<TextureAsset>(textureAssetRef.Key)->GetRenderTexture());
                }

                m_Renderer.Submit(
                    AssetManager::Get<MeshAsset>(material.Mesh.Key)->GetRenderMesh(),
                    AssetManager::Get<ShaderAsset>(material.Shader.Key)->GetShader(),
                    transform.Transform * glm::mat4_cast(transform.Rotation),
                    textures,
                    material.UniformName,
                    material.UniformData
                );
            }
        }

        {
            auto view = m_Registry.view<NativeScriptComponent>();

            for (auto & entity : view)
            {
                auto & nsc = view.get(entity);

                if (nsc.ScriptInstance)
                {
                    nsc.ScriptInstance->OnUpdate();
                }
            }
        }

        m_Renderer.Flush({0.8, 1.0, 0.8, 1.0});
    }

    void Scene::OnDestroy()
    {
        {
            auto view = m_Registry.view<NativeScriptComponent>();

            for (auto & entity : view)
            {
                auto & nsc = view.get(entity);

                nsc.DestroyInstanceFunction(nsc.ScriptInstance);
            }
        }
    }

    void Scene::OnResize(uint64_t width, uint64_t height)
    {
        {
            auto view = m_Registry.view<TransformComponent, CameraComponent>();

            for (auto & entity : view)
            {
                auto[transform, camera] = view.get<TransformComponent, CameraComponent>(entity);

                if (camera.MainCamera)
                {
                    camera.Recalculate(width, height);
                    break;
                }
            }
        }
    }

    std::vector<Entity> Scene::GetAllEntities()
    {
        std::vector<Entity> entities(m_Registry.size());

        auto view = m_Registry.view<TagComponent>();

        for (size_t i = 0; i < m_Registry.size(); i++)
        {
            entities[i] = Entity{view[i], &m_Registry};
        }

        return std::move(entities);
    }
}
