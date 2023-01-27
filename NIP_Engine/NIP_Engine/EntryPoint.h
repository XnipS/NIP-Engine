#pragma once
#include "Application.h"
extern NIP_Engine::Application* NIP_Engine::CreateApplication();

int main(int argc, char** argv)
{
    std::cout << "NIP_Engine ONLINE" << std::endl;
    auto app = NIP_Engine::CreateApplication();
    app->Run();
    delete app;
    return 0;
}
