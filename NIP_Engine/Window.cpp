#include "Window.h"
#include "core.h"
#include <GL/gl.h>
#include <SDL.h>
#include <SDL_events.h>
#include <SDL_opengl.h>
#include <SDL_video.h>

SDL_Window* win;
SDL_GLContext gl_context;
// ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

void NIP_Engine::Window::Initialise(const char* title, int w, int h)
{
    // SDL Attributes
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    // Create window with flags
    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL);
    win = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, w, h, window_flags);

    // Initialise renderer
    gl_context = SDL_GL_CreateContext(win);
    SDL_GL_MakeCurrent(win, gl_context);

    // Setup Done
    isRunning = true;
}

void NIP_Engine::Window::Update()
{
    // Tick
    tick++;

    // Handle events
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT)
            isRunning = false;
        if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(win))
            isRunning = false;
    }
}

void NIP_Engine::Window::Render()
{
    // Clear and render
    // glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GL_SwapWindow(win);
}

// Clean
void NIP_Engine::Window::Clean()
{

    // Clean SDL
    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(win);
    SDL_Quit();
    NE_LOG_INFO("Window Cleaned!");
}