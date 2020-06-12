#ifndef CHAKRA_SCENE_HPP
#define CHAKRA_SCENE_HPP

#include <unordered_map>

#include "core/ecs/Entity.hpp"
#include "core/ecs/System.hpp"

namespace Chakra
{
    class Scene
    {
        public:
            Scene(std::string id);

            Entity & addEntity(const EntityID & name);
            Entity & getEntity(const EntityID & name);
            void     removeEntity(const EntityID & name);

            void     addSystem(System * system);

            void Initialize();
            void Update();
            void Exit();

        private:
            std::string                          m_ID;
            std::unordered_map<EntityID, Entity> m_Entities;
            std::vector<System *>                m_Systems;
    };
}

#endif
