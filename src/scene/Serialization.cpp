#include "Serialization.hpp"

namespace Chakra
{
    std::string Serializer::Serialize(Entity & entity, YAML::Emitter & emitter, bool standalone)
    {
        if (standalone)
        {
            emitter<<YAML::BeginMap;
            emitter<<YAML::Key<<"FileType"<<YAML::Value<<"Entity";
        }

        emitter<<YAML::BeginMap;
        emitter<<YAML::Key<<"Components";
        emitter<<YAML::Value<<YAML::BeginSeq;

        if (entity.HasComponent<TagComponent>())
        {
            auto & tag = entity.GetComponent<TagComponent>();

            emitter<<YAML::BeginMap;
            emitter<<YAML::Key<<"ComponentType"<<YAML::Value<<"Tag";
            emitter<<YAML::Key<<"Tag"<<YAML::Value<<YAML::DoubleQuoted<<tag.Tag;
            emitter<<YAML::EndMap;
        }

        if (entity.HasComponent<TransformComponent>())
        {
            auto & transform = entity.GetComponent<TransformComponent>();

            glm::vec3 rotation(glm::eulerAngles(transform.Rotation));

            emitter<<YAML::BeginMap;
            emitter<<YAML::Key<<"ComponentType"<<YAML::Value<<"Transform";
            emitter<<YAML::Key<<"Position";
            emitter<<YAML::Value<<YAML::Flow<<YAML::BeginSeq;
            emitter<<transform.Transform[3][0]<<transform.Transform[3][1]<<transform.Transform[3][2];
            emitter<<YAML::EndSeq;
            emitter<<YAML::Key<<"Rotation";
            emitter<<YAML::Value<<YAML::Flow<<YAML::BeginSeq;
            emitter<<rotation.x<<rotation.y<<rotation.z;
            emitter<<YAML::EndSeq;
            emitter<<YAML::Key<<"Scale";
            emitter<<YAML::Value<<YAML::Flow<<YAML::BeginSeq;
            emitter<<transform.Transform[0][0]<<transform.Transform[1][1]<<transform.Transform[2][2];
            emitter<<YAML::EndSeq;
            emitter<<YAML::EndMap;
        }

        if (entity.HasComponent<MaterialComponent>())
        {
            auto & material = entity.GetComponent<MaterialComponent>();

            emitter<<YAML::BeginMap;
            emitter<<YAML::Key<<"ComponentType"<<YAML::Value<<"Material";
            emitter<<YAML::Key<<"Mesh"<<YAML::Value<<material.Mesh.Key;
            emitter<<YAML::Key<<"Shader"<<YAML::Value<<material.Shader.Key;
            emitter<<YAML::Key<<"Textures"<<YAML::Value;
            emitter<<YAML::Flow<<YAML::BeginSeq;
            
            for (auto & texture : material.Textures)
            {
                emitter<<texture.Key;
            }

            emitter<<YAML::EndSeq;
            emitter<<YAML::Key<<"UniformBlockName"<<YAML::Value<<material.UniformName;
            emitter<<YAML::Key<<"UniformVariables"<<YAML::Value<<YAML::BeginSeq;
            emitter<<YAML::BeginMap;


            for (auto & uniformFormat : AssetManager::Get<ShaderAsset>(material.Shader.Key)->GetShader().GetUniformFormats())
            {
                if (uniformFormat.Name == material.UniformName)
                {
                    size_t offset = 0;

                    if (material.UniformData.size() != uniformFormat.Size)
                    {
                        material.UniformData.resize(uniformFormat.Size);
                    }

                    for (auto & member : uniformFormat.Members)
                    {
                        if (member.Type.basetype == spirv_cross::SPIRType::BaseType::Float && member.Type.columns == 0)
                        {
                            emitter<<YAML::Key<<member.Name<<YAML::Value;
                            emitter<<YAML::BeginMap;
                            emitter<<YAML::Key<<"Type"<<YAML::Value<<YAML::DoubleQuoted<<"Float";
                            emitter<<YAML::Key<<"Value"<<YAML::Value<<*(float *)material.UniformData.data();
                            emitter<<YAML::EndMap;
                        }
                        else if (member.Type.columns == 1)
                        {
                            if (member.Type.vecsize == 2)
                            {
                                emitter<<YAML::Key<<member.Name<<YAML::Value;
                                emitter<<YAML::BeginMap;
                                emitter<<YAML::Key<<"Type"<<YAML::Value<<YAML::DoubleQuoted<<"Vector2";
                                emitter<<YAML::Key<<"Value"<<YAML::Value<<YAML::Flow<<YAML::BeginSeq;
                                emitter<<((float *)(material.UniformData.data() + offset))[0];
                                emitter<<((float *)(material.UniformData.data() + offset))[1];
                                emitter<<YAML::EndSeq;
                                emitter<<YAML::EndMap;
                            }
                            else if (member.Type.vecsize == 3)
                            {
                                emitter<<YAML::Key<<member.Name<<YAML::Value;
                                emitter<<YAML::BeginMap;
                                emitter<<YAML::Key<<"Type"<<YAML::Value<<YAML::DoubleQuoted<<"Vector3";
                                emitter<<YAML::Key<<"Value"<<YAML::Value<<YAML::Flow<<YAML::BeginSeq;
                                emitter<<((float *)(material.UniformData.data() + offset))[0];
                                emitter<<((float *)(material.UniformData.data() + offset))[1];
                                emitter<<((float *)(material.UniformData.data() + offset))[2];
                                emitter<<YAML::EndSeq;
                                emitter<<YAML::EndMap;
                            }
                            else if (member.Type.vecsize == 4)
                            {
                                emitter<<YAML::Key<<member.Name<<YAML::Value;
                                emitter<<YAML::BeginMap;
                                emitter<<YAML::Key<<"Type"<<YAML::Value<<YAML::DoubleQuoted<<"Vector4";
                                emitter<<YAML::Key<<"Value"<<YAML::Value<<YAML::Flow<<YAML::BeginSeq;
                                emitter<<((float *)(material.UniformData.data() + offset))[0];
                                emitter<<((float *)(material.UniformData.data() + offset))[1];
                                emitter<<((float *)(material.UniformData.data() + offset))[2];
                                emitter<<((float *)(material.UniformData.data() + offset))[3];
                                emitter<<YAML::EndSeq;
                                emitter<<YAML::EndMap;
                            }
                        }

                        offset += member.Size;
                    }
                }
            }


            emitter<<YAML::EndMap;
            emitter<<YAML::EndSeq;
            emitter<<YAML::EndMap;
        }

        if (entity.HasComponent<CameraComponent>())
        {
            auto & camera = entity.GetComponent<CameraComponent>();

            emitter<<YAML::BeginMap;
            emitter<<YAML::Key<<"ComponentType"<<YAML::Value<<"Camera";
            emitter<<YAML::Key<<"MainCamera"<<YAML::Value<<camera.MainCamera;
            emitter<<YAML::Key<<"ProjectionType"<<YAML::Value<<(camera.Type == CameraComponent::CameraType::PERSPECTIVE ? "PERSPECTIVE" : "ORTHOGRAPHIC");
            emitter<<YAML::Key<<"PerspectiveFOV"<<YAML::Value<<camera.PerspectiveFOV;
            emitter<<YAML::Key<<"PerspectiveNear"<<YAML::Value<<camera.PerspectiveNear;
            emitter<<YAML::Key<<"PerspectiveFar"<<YAML::Value<<camera.PerspectiveFar;
            emitter<<YAML::Key<<"OrthographicScale"<<YAML::Value<<camera.OrthographicScale;
            emitter<<YAML::Key<<"OrthographicNear"<<YAML::Value<<camera.OrthographicNear;
            emitter<<YAML::Key<<"OrthographicFar"<<YAML::Value<<camera.OrthographicFar;
            emitter<<YAML::EndMap;
        }

        emitter<<YAML::EndSeq;
        emitter<<YAML::EndMap;

        if (standalone)
        {
            emitter<<YAML::EndMap;
        }
        
        CHK_ASSERT(emitter.good(), "Serializer", "Emitter error in entity `", entity.GetComponent<TagComponent>().Tag, "` : ", emitter.GetLastError(), ".");

        return std::move(std::string(emitter.c_str()));
    }

    std::string Serializer::Serialize(Scene & scene)
    {
        YAML::Emitter emitter;

        emitter<<YAML::BeginMap;
        emitter<<YAML::Key<<"FileType"<<YAML::Value<<"Scene";
        emitter<<YAML::Key<<"Entities"<<YAML::Value<<YAML::BeginSeq;

        for (auto & entity : scene.GetAllEntities())
        {
            Serialize(entity, emitter, false);
        }

        emitter<<YAML::EndSeq;
        emitter<<YAML::EndMap;

        CHK_ASSERT(emitter.good(), "Serializer", "Emitter error: ", emitter.GetLastError(), ".");

        return std::move(std::string(emitter.c_str()));
    }

    void Serializer::DeserializeEntity(Entity & entity, YAML::Node entityNode)
    {
        if (YAML::Node components = entityNode["Components"])
        {
            for (auto iter = components.begin(); iter != components.end(); ++iter)
            {
                YAML::Node component = *iter;

                if (component["ComponentType"].as<std::string>() == "Tag")
                {
                    entity.AddComponent<TagComponent>(component["Tag"].as<std::string>());
                }
                else if (component["ComponentType"].as<std::string>() == "Transform")
                {
                    YAML::Node positionNode = component["Position"];
                    YAML::Node rotationNode = component["Rotation"];
                    YAML::Node scaleNode = component["Scale"];

                    auto & transform = entity.AddComponent<TransformComponent>(
                        glm::mat4
                        {
                            scaleNode[0].as<float>(), 0.0f, 0.0f, positionNode[0].as<float>(),
                            0.0f, scaleNode[1].as<float>(), 0.0f, positionNode[1].as<float>(),
                            0.0f, 0.0f, scaleNode[2].as<float>(), positionNode[2].as<float>(),
                            0.0f, 0.0f, 0.0f, 1.0f
                        }
                    );

                    transform.Rotate(rotationNode[0].as<float>(), rotationNode[1].as<float>(), rotationNode[2].as<float>());
                }
                else if (component["ComponentType"].as<std::string>() == "Material")
                {
                    std::vector<AssetReference> textures;

                    for (auto iter = component["Textures"].begin(); iter != component["Textures"].end(); ++iter)
                    {
                        textures.emplace_back(AssetReference{iter->as<std::string>()});
                    }

                    std::vector<uint8_t> uniformData;
                    
                    for (auto iter = component["UniformVariables"][0].begin(); iter != component["UniformVariables"][0].end(); ++iter)
                    {
                        auto var = iter->second;

                        if (var["Type"].as<std::string>() == "Float")
                        {
                            float data = var["Value"].as<float>();

                            uniformData.resize(uniformData.size() + 8);
                            memcpy(uniformData.data(), &data, 4);
                            memset(uniformData.data() + 4, '\0', 4);

                        }
                        else if (var["Type"].as<std::string>() == "Vector2")
                        {
                            glm::vec2 data = glm::vec2{var["Value"][0].as<float>(), var["Value"][1].as<float>()};

                            uniformData.resize(uniformData.size() + 8);
                            memcpy(uniformData.data(), glm::value_ptr(data), 8);
                        }
                        else if (var["Type"].as<std::string>() == "Vector3")
                        {
                            glm::vec3 data = glm::vec3{var["Value"][0].as<float>(), var["Value"][1].as<float>(), var["Value"][2].as<float>()};

                            uniformData.resize(uniformData.size() + 16);
                            memcpy(uniformData.data(), glm::value_ptr(data), 12);
                            memset(uniformData.data() + 12, '\0', 4);
                        }
                        else if (var["Type"].as<std::string>() == "Vector4")
                        {
                            glm::vec4 data = glm::vec4{var["Value"][0].as<float>(), var["Value"][1].as<float>(), var["Value"][2].as<float>(), var["Value"][3].as<float>()};

                            uniformData.resize(uniformData.size() + 16);
                            memcpy(uniformData.data(), glm::value_ptr(data), 16);
                        }
                    }

                    entity.AddComponent<MaterialComponent>(
                        AssetReference{component["Mesh"].as<std::string>()},
                        AssetReference{component["Shader"].as<std::string>()},
                        component["UniformBlockName"].as<std::string>(),
                        std::move(uniformData)
                    ).Textures = std::move(textures);
                }
                else if (component["ComponentType"].as<std::string>() == "Camera")
                {
                    auto & camera = entity.AddComponent<CameraComponent>(
                        component["MainCamera"].as<bool>(),
                        component["ProjectionType"].as<std::string>() == "Perspective" ? CameraComponent::CameraType::PERSPECTIVE : CameraComponent::CameraType::ORTHOGRAPHIC
                    );

                    camera.PerspectiveFOV = component["PerspectiveFOV"].as<float>();
                    camera.PerspectiveNear = component["PerspectiveNear"].as<float>();
                    camera.PerspectiveFar = component["PerspectiveFar"].as<float>();

                    camera.OrthographicScale = component["OrthographicScale"].as<float>();
                    camera.OrthographicNear = component["OrthographicNear"].as<float>();
                    camera.OrthographicFar = component["OrthographicFar"].as<float>();
                }
            }
        }
    }

    void Serializer::DeserializeEntity(Entity & entity, const std::string & data)
    {
        CHK_ASSERT(entity.IsValid(), "Serializer", "Invalid entity as target.");

        YAML::Node entityNode = YAML::Load(data.c_str());

        CHK_ASSERT(entityNode["FileType"].as<std::string>() == "Entity", "Serializer", "Data is not of type `Entity`.");

        DeserializeEntity(entity, entityNode);
    }

    void Serializer::DeserializeScene(Scene & scene, const std::string & data)
    {
        new(&scene) Scene();

        YAML::Node sceneNode = YAML::Load(data.c_str());

        CHK_ASSERT(sceneNode["FileType"].as<std::string>() == "Scene", "Serializer", "Data is not of type `Scene`.");

        for (auto iter = sceneNode["Entities"].begin(); iter != sceneNode["Entities"].end(); ++iter)
        {
            Entity entity = scene.AddEntity("");
            entity.RemoveComponent<TagComponent>();

            DeserializeEntity(entity, *iter);
        }
    }
}
