#ifndef CHAKRA_SCENE_COMPONENTS_HPP
#define CHAKRA_SCENE_COMPONENTS_HPP

#include "core/Common.hpp"
#include "core/AssetManager.hpp"

#include "assets/MeshAsset.hpp"
#include "assets/ShaderAsset.hpp"
#include "assets/TextureAsset.hpp"

#include "scripting/NativeScript.hpp"

namespace Chakra
{
    struct TagComponent
    {
        std::string Tag;

        TagComponent() = default;
        TagComponent(const TagComponent &) = default;

        TagComponent(const std::string & tag)
            : Tag(tag)
        {
        }
    };

    struct TransformComponent
    {
        glm::mat4 Transform;
        glm::quat Rotation;

        TransformComponent() = default;
        TransformComponent(const TransformComponent &) = default;

        TransformComponent(const glm::mat4 & transform, const glm::quat & rotation = glm::quat{0.0f, 0.0f, 0.0f, 1.0f})
            : Transform(transform), Rotation(rotation)
        {
        }

        operator glm::mat4() { return Transform; }
        operator const glm::mat4() const { return Transform; }

        void Translate(float x, float y, float z)
        {
            Transform = glm::translate(Transform, glm::vec3{x, y, z});
        }

        void Translate(glm::vec3 translation)
        {
            Transform = glm::translate(Transform, translation);
        }

        void Rotate(float x, float y, float z)
        {
            Rotation = glm::rotate(Rotation, glm::radians(x), glm::vec3{1.0, 0.0, 0.0});
            Rotation = glm::rotate(Rotation, glm::radians(y), glm::vec3{0.0, 1.0, 0.0});
            Rotation = glm::rotate(Rotation, glm::radians(z), glm::vec3{0.0, 0.0, 1.0});
        }

        void Rotate(glm::vec3 rotation)
        {
            Rotation = glm::rotate(Rotation, glm::radians(rotation.x), glm::vec3{1.0, 0.0, 0.0});
            Rotation = glm::rotate(Rotation, glm::radians(rotation.y), glm::vec3{0.0, 1.0, 0.0});
            Rotation = glm::rotate(Rotation, glm::radians(rotation.z), glm::vec3{0.0, 0.0, 1.0});
        }

        void Scale(float x, float y, float z)
        {
            Transform = glm::scale(Transform, glm::vec3{x, y, z});
        }

        void Scale(glm::vec3 scale)
        {
            Transform = glm::scale(Transform, scale);
        }
    };

    struct MaterialComponent
    {
        AssetReference Mesh;
        AssetReference Shader;

        std::vector<AssetReference> Textures;

        std::string          UniformName;
        std::vector<uint8_t> UniformData;

        MaterialComponent() = default;
        MaterialComponent(const MaterialComponent &) = default;

        MaterialComponent(AssetReference mesh, AssetReference shader, const std::string & uniformName = "", std::vector<uint8_t> data = {})
            : Mesh(mesh), Shader(shader), UniformName(uniformName), UniformData(data)
        {
        }
    };

    struct CameraComponent
    {
        enum class CameraType
        {
            PERSPECTIVE,
            ORTHOGRAPHIC
        };

        bool MainCamera = false;

        CameraType Type = CameraType::PERSPECTIVE;
        float PerspectiveFOV = 45.0f;
        float PerspectiveNear = 0.01f;
        float PerspectiveFar = 1000.0f;

        float OrthographicScale = 10.0f;
        float OrthographicNear = -1.0f;
        float OrthographicFar = 1.0f;

        glm::mat4 ProjectionMatrix;
        
        CameraComponent() = default;
        CameraComponent(const CameraComponent &) = default;

        CameraComponent(bool mainCamera, CameraType type)
            : MainCamera(mainCamera), Type(type)
        {
        }

        void Recalculate(uint64_t width, uint64_t height)
        {
            if (Type == CameraComponent::CameraType::PERSPECTIVE)
            {
                ProjectionMatrix = glm::perspective<float>(
                    glm::radians(PerspectiveFOV),
                    (float)width / (float)height,
                    PerspectiveNear, PerspectiveFar
                );
            }
            else
            {
                float heightByWidth = (float)height / (float) width;

                ProjectionMatrix = glm::ortho<float>(
                    -OrthographicScale, OrthographicScale,
                    heightByWidth * -OrthographicScale, heightByWidth * OrthographicScale,
                    OrthographicNear, OrthographicFar
                );
            }
        }
    };

    struct NativeScriptComponent
    {
        Scripting::NativeScript * ScriptInstance;

        void( * CreateInstanceFunction)(Entity, Scripting::NativeScript **);
        void( * DestroyInstanceFunction)(Scripting::NativeScript *);

        NativeScriptComponent() = default;
        NativeScriptComponent(const NativeScriptComponent &) = default;

        template <typename T>
        void Bind()
        {
            CreateInstanceFunction = [](Entity entity, Scripting::NativeScript ** instancePtr){ *instancePtr = new T(); (*instancePtr)->SetEntity(entity); };
            DestroyInstanceFunction = [](Scripting::NativeScript * instance){ delete (T *)instance; };
        }
    };
}

#endif
