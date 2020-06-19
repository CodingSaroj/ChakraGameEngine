#ifndef CHAKRA_ENTRY_POINT_HPP
#define CHAKRA_ENTRY_POINT_HPP

#include "core/Common.hpp"

#include "core/Logger.hpp"
#include "core/Application.hpp"

extern std::ostream &                     GetLogOStream();
extern Chakra::Application *              CreateApplication();
extern std::vector<std::function<void()>> GetStartUpFunctions();

int main()
{
    Chakra::Logger::Initialize();

    auto functions = GetStartUpFunctions();

    for (auto function : functions)
    {
        function();
    }

    Chakra::Application * app = CreateApplication();

    app->run();

    delete app;
}

#endif
