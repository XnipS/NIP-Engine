#include "BMP_Loader.h"
#include "Entity.h"
#include "EntityCamera.h"
#include "EntityRenderer.h"
#include "EntityTransform.h"
#define GLM_ENABLE_EXPERIMENTAL
#include "Window.h"
#include "core.h"
#include <GL/gl.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <ios>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

GLFWwindow* win; // Window
NIP_Engine::Camera* mainCamera;
NIP_Engine::EntitySystem entitySystem;
NIP_Engine::EntityRenderer entityRenderer;
NIP_Engine::EntityCamera entityCamera;
NIP_Engine::EntityTransform entityTransform;

glm::mat4 mvpMatrix = glm::mat4(1.0f); // Perspective matrix (without model matrix)
glm::mat4 viewMatrix = glm::mat4(1.0f); // View matrix

void NIP_Engine::Window::Initialise(const char* title, int w, int h)
{
    // Pass window variables
    width = w;
    height = h;

    // Check if GLFW is working
    if (!glfwInit()) {
        NE_LOG_ERROR("Failed to initialize GLFW\n");
    }

    // GLFW hints
    glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // We still want OpenGL 3
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL

    // Open a window and create a OpenGL context
    win = glfwCreateWindow(width, height, title, glfwGetPrimaryMonitor(), NULL);
    if (win == NULL) {
        NE_LOG_ERROR("Failed to open GLFW window\n");
        glfwTerminate();
    }

    // Initialise GLEW
    glfwMakeContextCurrent(win);
    glewExperimental = true;
    glewInit();

    // Setup Done
    isRunning = true;

    // Create camera object
    Entity cam = entitySystem.CreateGameObject();

    mainCamera = entityCamera.CreateCamera(cam.GetObjectID(), width, height);

    // Create new object
    Entity cube = entitySystem.CreateGameObject();

    // Create new renderer for cube
    entityTransform.CreateTransform(cube.GetObjectID());
    entityRenderer.CreateMeshRenderer(cube.GetObjectID(), "../../NIP_Engine/Models/cube.obj");
    entityRenderer.GetMeshRenderer(cube.GetObjectID())->LinkMatrices(&mvpMatrix, &viewMatrix);

    // Create new object
    Entity sphere = entitySystem.CreateGameObject();

    // Create new renderer for cube
    entityTransform.CreateTransform(sphere.GetObjectID());
    entityRenderer.CreateMeshRenderer(sphere.GetObjectID());
    entityRenderer.GetMeshRenderer(sphere.GetObjectID())->LinkMatrices(&mvpMatrix, &viewMatrix);

    // Initialise all entity renderers
    // TODO: Start on creation of new mesh renderer to summon objects on update
    entityRenderer.Start();
}

void NIP_Engine::Window::GetWindowDimension(int* w, int* h)
{
    *w = width;
    *h = height;
}

void NIP_Engine::Window::Update()
{
    // Tick
    tick++;

    // Handle events
    glfwPollEvents();

    // Grab cursor events
    double xpos, ypos;
    glfwGetCursorPos(win, &xpos, &ypos);
    glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPos(win, width / 2.0, height / 2.0);

    // Pass input events to camera
    mainCamera->PassUserInput(&xpos, &ypos, (glfwGetKey(win, GLFW_KEY_W) == GLFW_PRESS), (glfwGetKey(win, GLFW_KEY_S) == GLFW_PRESS), (glfwGetKey(win, GLFW_KEY_A) == GLFW_PRESS), (glfwGetKey(win, GLFW_KEY_D) == GLFW_PRESS), (glfwGetKey(win, GLFW_KEY_SPACE) == GLFW_PRESS), (glfwGetKey(win, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS));

    // Calculate Perspective
    mainCamera->CalculatePerspective(&mvpMatrix, &viewMatrix);

    // Check if should close
    if (glfwWindowShouldClose(win)) {
        isRunning = false;
    }
}

void NIP_Engine::Window::Render()
{
    // Clear
    glClearColor(0.16, 0.16, 0.16, 1.0); // Set clear colour
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear

    // Enable special features
    glEnable(GL_DEPTH_TEST); // Enable depth test
    glEnable(GL_CULL_FACE); // Cull backfaces
    glDepthFunc(GL_LESS); // Accept fragment if it closer to the camera than the former one

    // Update entities
    entityRenderer.Update(&entityTransform);

    // Swap buffers
    glfwSwapBuffers(win);
}

// Clean
void NIP_Engine::Window::Clean()
{
    NE_LOG_INFO("Window Cleaned!\n");
}
