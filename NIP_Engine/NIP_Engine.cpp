#include "Window.h"
#include "core.h"
#include <GL/freeglut.h>
#include <chrono>
#include <iostream>
#include <stdio.h>
#include <thread>

// Add hook
// extern NIP_Engine::Application *NIP_Engine::CreateApplication();

NIP_Engine::Window* app = nullptr;
// NIP_Engine::Render* window = nullptr;
int frameStart;
int currentTickTime;
// Entrypoint
int main(int argc, char* args[])
{
    // Create new window
    app = new NIP_Engine::Window();

    // Start
    app->Initialise("NIP-Engine", 1280, 720);

    // Tick loop
    while (app->Running()) {
        // Start tick time
        frameStart = glutGet(GLUT_ELAPSED_TIME);

        app->Update();
        app->Render();

        // Check for delays
        currentTickTime = glutGet(GLUT_ELAPSED_TIME) - frameStart;
        if (NE_TICKRATE_TIME > currentTickTime) {
            std::this_thread::sleep_for(std::chrono::milliseconds(NE_TICKRATE_TIME - currentTickTime));
        } else {
            NE_LOG_INFO("Tickrate lagging: %i ms behind!\n", (currentTickTime - NE_TICKRATE_TIME));
        }
    }

    // Clean
    app->Clean();

    /* 	 NIP_Engine::Log::Init();
      NE_CORE_INFO("NIP-Engine Initialised!");
      auto app = NIP_Engine::CreateApplication();
      app->Run();
      delete app;
      return 0; */
    NE_LOG_INFO("Goodbye!\n");

    return 0;
}