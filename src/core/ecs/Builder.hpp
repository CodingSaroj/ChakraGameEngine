#ifndef CHAKRA_BUILDER_HPP
#define CHAKRA_BUILDER_HPP

#include "core/ecs/Scene.hpp"

namespace Chakra
{
    namespace Builder
    {
        namespace Private
        {
            extern bool   inScene;
            extern bool   inEntity;
            extern Scene  currentScene;
            extern Entity currentEntity;
        }

        void BeginScene(std::string name);
        void BeginEntity(EntityID name);

        template <typename T>
        void AddComponent(const T & component)
        {
            if (Private::inScene && Private::inEntity)
            {
                Private::currentEntity.addComponent<T>(component);
            }
            else
            {
                Logger::LogError("Builder", "Trying add component without beginning an entity or beginning a scene");
                exit(-1);
            }
        }

        void     EndEntity();
        Scene && EndScene();
    }
}

#endif
