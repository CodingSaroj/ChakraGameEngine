#ifndef CHAKRA_COMPONENT_MANAGER_HPP
#define CHAKRA_COMPONENT_MANAGER_HPP

#include <iostream>
#include <unordered_map>
#include <vector>

#include "core/Logger.hpp"

namespace Chakra
{
    using EntityID = std::string;

    template <typename T>
    class ComponentManager
    {
        public:
            static void Register(EntityID id, const T & component)
            {
                if (components.count() == 0)
                {
                    components.insert(std::pair<EntityID, T>(id, component));
                }
                else
                {
                    Logger::LogWarning("ECS", "Trying to add component to an entity that already has it");
                }
            }

            static void Remove(EntityID id)
            {
                if (components.count() == 1)
                {
                    components.erase(components.find(id));
                }
                else
                {
                    Logger::LogWarning("ECS", "Trying to remove component on an entity that doesn't has it");
                }
            }

            static T & Get(EntityID id)
            {
                if (components.count() == 1)
                {
                    return components[id];
                }
                else
                {
                    Logger::LogError("ECS", "Trying to get component from an entity that doesn't has it");
                    exit(-1);
                }
            }

            static std::vector<T> GetAll()
            {
                std::vector<T> array;
                array.insert(components.begin(), components.end());
                return array;
            }

        private:
            static std::unordered_map<EntityID, T> components;
    };

    template <typename T>
    std::unordered_map<EntityID, T> ComponentManager<T>::components;
}

#endif
