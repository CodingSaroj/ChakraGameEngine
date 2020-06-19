#include "Builder.hpp"

namespace Chakra
{
    bool           Builder::Private::inScene  = false;
    bool           Builder::Private::inEntity = false;
    Scene  Builder::Private::currentScene("");
    Entity Builder::Private::currentEntity("");
    
    void Builder::BeginScene(std::string name)
    {
        if (!Private::inScene)
        {
            Private::inScene = true;
            Private::currentScene = Scene(name);
        }
        else
        {
            Logger::LogError("Builder", "Trying to begin a scene without ending previous one");
            exit(-1);
        }
    }
    
    void Builder::BeginEntity(EntityID name)
    {
        if (Private::inScene && !Private::inEntity)
        {
            Private::inEntity = true;
            Private::currentEntity = Private::currentScene.addEntity(name);
        }
        else
        {
            Logger::LogError("Builder", "Trying to begin an entity without ending one or without beginning a scene");
            exit(-1);
        }
    }
    
    void Builder::EndEntity()
    {
        if (Private::inEntity)
        {
            Private::inEntity = false;
        }
        else
        {
            Logger::LogError("Builder", "Trying to end an entity without beginning one");
            exit(-1);
        }
    }
    
    Scene && Builder::EndScene()
    {
        if (Private::inScene && !Private::inEntity)
        {
            Private::inScene = false;
            return std::move(Private::currentScene);
        }
        else
        {
            Logger::LogError("Builder", "Trying to end scene without beginning a scene or without ending an entity");
            exit(-1);
        }
    }
}
