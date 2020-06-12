#include "Builder.hpp"

bool           Chakra::Builder::Private::inScene  = false;
bool           Chakra::Builder::Private::inEntity = false;
Chakra::Scene  Chakra::Builder::Private::currentScene("");
Chakra::Entity Chakra::Builder::Private::currentEntity("");

void Chakra::Builder::BeginScene(std::string name)
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

void Chakra::Builder::BeginEntity(EntityID name)
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

void Chakra::Builder::EndEntity()
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

Chakra::Scene && Chakra::Builder::EndScene()
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
