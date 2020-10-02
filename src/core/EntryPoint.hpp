#ifndef CHAKRA_CORE_ENTRY_POINT_HPP
#define CHAKRA_CORE_ENTRY_POINT_HPP

#include "core/Common.hpp"
#include "core/Logger.hpp"
#include "core/Application.hpp"

extern std::ostream &        GetLogOStream();
extern Chakra::Application * GetApplication();

int main()
{
    Chakra::Logger::SetOStream(GetLogOStream());

    Chakra::Application & app = Chakra::Application::Instance(GetApplication());

    app.Run();
}

#endif
