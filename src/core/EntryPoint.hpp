#ifndef CHAKRA_ENTRY_POINT_HPP
#define CHAKRA_ENTRY_POINT_HPP

#include "core/Logger.hpp"
#include "core/Application.hpp"

extern std::ostream &        GetLogOStream();
extern Chakra::Application * CreateApplication();

int main()
{
    Chakra::Logger::Initialize(GetLogOStream());

    Chakra::Application * app = CreateApplication();

    app->run();

    delete app;
}

#endif
