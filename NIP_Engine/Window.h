#pragma once

#include <GL/glew.h>
namespace NIP_Engine {

class Window {
public:
    void Initialise(const char* title, int w, int h);
    void Update();
    void Render();
    void Clean();
    bool Running() { return isRunning; };

private:
    bool isRunning = false;
    int tick = 0;
    GLuint LoadShaders(const char* vertex_path, const char* frag_path);
};
}