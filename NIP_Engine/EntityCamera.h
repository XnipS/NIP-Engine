#pragma once

#include "Entity.h"
#include <vector>
namespace NIP_Engine {
class Camera : public Component {
public:
    // Camera(Window* win);
    void Start() override;

    void Update() override;

    void CalculatePerspective(glm::mat4* projection);
    void PassUserInput(double* mouse_x, double* mouse_y, bool forward, bool backward, bool left, bool right, bool up, bool down);

    void SetWindowSize(int w, int h)
    {
        window_height = h;
        window_width = w;
    }

private:
    int window_height, window_width;
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

;

class EntityCamera {
public:
    void Start()
    {
        for (int i = 0; i < cameras.size(); i++) {
            cameras[i].Start();
        }
    }
    void Update()
    {
        for (int i = 0; i < cameras.size(); i++) {
            cameras[i].Update();
        }
    }
    Camera* CreateCamera(int owner, int w, int h);
    std::vector<Camera> cameras;

private:
};
}