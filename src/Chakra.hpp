#ifndef CHAKRA_HPP
#define CHAKRA_HPP

#include "core/Application.hpp"
#include "core/EntryPoint.hpp"
#include "core/ecs/Scene.hpp"
#include "core/ecs/Builder.hpp"

#include "core/AssetManager.hpp"
#include "core/Assets.hpp"

namespace Chakra
{
    std::vector<std::function<void()>> GetStartUpFunctions()
    {
        return { Setup };
    }
}

#endif
