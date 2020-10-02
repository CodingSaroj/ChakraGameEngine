#ifndef CHAKRA_SCENE_SCENE_HPP
#define CHAKRA_SCENE_SCENE_HPP

#include "core/Common.hpp"
#include "core/AssetManager.hpp"

#include "scene/Entity.hpp"
#include "scene/Components.hpp"

#include "renderer/Renderer.hpp"

#include <entt/entt.hpp>

namespace Chakra
{
    class Scene
    {
    public:
        Scene() = default;

        Entity AddEntity(const std::string & tag = "Entity");
        void   RemoveEntity(Entity entity);

        void OnCreate();
        void OnUpdate();
        void OnDestroy();
        void OnResize(uint64_t width, uint64_t height);

        std::vector<Entity> GetAllEntities();

    private:
        entt::registry m_Registry;

        Renderer m_Renderer;

        friend class Serializer;
    };
}

#endif
