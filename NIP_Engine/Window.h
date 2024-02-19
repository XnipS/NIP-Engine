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
    GLuint LoadShaders(const char* vertex_path, const char* frag_path);
};

class Camera {
public:
    Camera(Window* win);

    void CalculatePerspective(glm::mat4* projection);
    void PassUserInput(double* mouse_x, double* mouse_y, bool forward, bool backward, bool left, bool right, bool up, bool down);

private:
    Window* boundedWindow;
    glm::vec3 position
        = glm::vec3(0, 0, 0);
    float horizontalAngle = 0.0f;
    float verticalAngle = 0.0f;
    float fieldOfView = 90.0f;
    float moveSpeed = 0.05f;
    float lookSpeed = 0.05f;

    glm::vec3 dir_forward;
    glm::vec3 dir_right;
    glm::vec3 dir_up;
};
}