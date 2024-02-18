#include "core.h"
#include <iostream>
#include <stdio.h>

// Add hook
// extern NIP_Engine::Application *NIP_Engine::CreateApplication();
// Entrypoint

int main(int argc, char* args[])
{
    /* 	 NIP_Engine::Log::Init();
      NE_CORE_INFO("NIP-Engine Initialised!");
      auto app = NIP_Engine::CreateApplication();
      app->Run();
      delete app;
      return 0; */
    NE_LOG_INFO("Done!");

    // std::cout << "Done!" << std::endl;
    return 0;
}