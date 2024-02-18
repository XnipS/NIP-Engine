#pragma once

namespace NIP_Engine {

class Window {
public:
    void Initialise(const char* title, int w, int h);
    void Update();
    void Render();
    void Clean();
    bool Running() { return isRunning; };

private:
    bool isRunning;
    int tick = 0;
};
}