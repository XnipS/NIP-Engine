#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
namespace NIP_Engine {

class Window {
public:
    void Initialise(const char* title, int w, int h);
    void Update();
    void Render();
    void Clean();
    bool Running() { return isRunning; };
    void GetWindowDimension(int* w, int* h);

private:
    bool isRunning = false;
    int tick = 0;
    int width;
    int height;
};
}