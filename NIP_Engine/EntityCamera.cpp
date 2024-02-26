#include "EntityCamera.h"
#include "core.h"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

NIP_Engine::Camera* NIP_Engine::EntityCamera::CreateCamera(int owner, int w, int h)
{
    Camera newObject = Camera();
    newObject.ownerID = owner;
    newObject.SetWindowSize(w, h);
    cameras.push_back(newObject);
    // newObject.Start();
    return &cameras.back();
}

void NIP_Engine::Camera::Start()
{
}

void NIP_Engine::Camera::Update()
{
}

void NIP_Engine::Camera::PassUserInput(double* mouse_x, double* mouse_y, bool forward, bool backward, bool left, bool right, bool up, bool down)
{
    // Called on fixedupdate

    // Mouselook
    horizontalAngle += lookSpeed * NE_DELTATIME * float(window_width / 2.0 - *mouse_x);
    verticalAngle += lookSpeed * NE_DELTATIME * float(window_height / 2.0 - *mouse_y);

    // Clamp vertical angle
    if (verticalAngle > NE_PI / 2) {
        verticalAngle = NE_PI / 2;
    } else if (verticalAngle < -NE_PI / 2) {
        verticalAngle = -NE_PI / 2;
    }

    // Forward vector : Spherical coordinates to Cartesian coordinates conversion
    dir_forward = glm::vec3(cos(verticalAngle) * sin(horizontalAngle), sin(verticalAngle),
        cos(verticalAngle) * cos(horizontalAngle));
    // Right vector
    dir_right = glm::vec3(sin(horizontalAngle - NE_PI / 2.0f), 0, cos(horizontalAngle - NE_PI / 2.0f));
    // Up vector
    dir_up = glm::cross(dir_right, dir_forward);

    // Move forward
    if (forward) {
        position += dir_forward * moveSpeed;
    }
    // Move backward
    if (backward) {
        position -= dir_forward * moveSpeed;
    }
    // Strafe right
    if (right) {
        position += dir_right * moveSpeed;
    }
    // Strafe left
    if (left) {
        position -= dir_right * moveSpeed;
    }
    // Vertical up
    if (up) {
        position += dir_up * moveSpeed;
    }
    // Vertical down
    if (down) {
        position -= dir_up * moveSpeed;
    }
}

void NIP_Engine::Camera::CalculatePerspective(glm::mat4* mvp, glm::mat4* vmatrix)
{
    // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
    glm::mat4 calculatedProjection = glm::perspective(glm::radians(fieldOfView), (float)window_width / (float)window_height, 0.01f, 100.0f);

    // Camera matrix
    glm::mat4 View = glm::lookAt(
        position, // Position
        position + dir_forward, // Direction
        dir_up // Which way is up
    );

    // Our ModelViewProjection : multiplication of our 3 matrices
    *mvp = calculatedProjection * View; // * Model; // Remember, matrix multiplication is the other way around
    *vmatrix = View;
}