#include "Window.h"
#include "core.h"
#include <SDL2/SDL.h>
#include <iostream>
#include <stdio.h>

// Add hook
// extern NIP_Engine::Application *NIP_Engine::CreateApplication();

NIP_Engine::Window* window = nullptr;
Uint32 frameStart;
int currentTickTime;
// Entrypoint
int main(int argc, char* args[])
{
    // Create new window
    window = new NIP_Engine::Window();

    // Start
    window->Initialise("NIP-Engine", 1280, 720);

    // Tick loop
    // Tick loop
    while (window->Running()) {
        // Start tick time
        frameStart = SDL_GetTicks();

        window->Update();
        window->Render();

        // Check for delays
        currentTickTime = SDL_GetTicks() - frameStart;

        if (NE_TICKRATE_TIME > currentTickTime) {
            SDL_Delay(NE_TICKRATE_TIME - currentTickTime);
        } else {
            std::cout << "Tickrate lagging: ";
            std::cout << (currentTickTime - NE_TICKRATE_TIME);
            std::cout << "ms behind!" << std::endl;
        }
    }

    // Clean
    window->Clean();

    /* 	 NIP_Engine::Log::Init();
      NE_CORE_INFO("NIP-Engine Initialised!");
      auto app = NIP_Engine::CreateApplication();
      app->Run();
      delete app;
      return 0; */
    NE_LOG_INFO("Done!");

    return 0;
}