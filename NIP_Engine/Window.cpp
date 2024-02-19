#include "BMP_Loader.h"
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
GLuint VAO;
GLuint vertexbuffer;
GLuint uvbuffer;
GLuint programID; // Shader program for triangle
glm::mat4 mvp; // View matrix

// Two UV coordinatesfor each vertex. They were created with Blender. You'll learn shortly how to do this yourself.
static const GLfloat cube_uv_data[] = {
    0.000059f, 1.0f - 0.000004f,
    0.000103f, 1.0f - 0.336048f,
    0.335973f, 1.0f - 0.335903f,
    1.000023f, 1.0f - 0.000013f,
    0.667979f, 1.0f - 0.335851f,
    0.999958f, 1.0f - 0.336064f,
    0.667979f, 1.0f - 0.335851f,
    0.336024f, 1.0f - 0.671877f,
    0.667969f, 1.0f - 0.671889f,
    1.000023f, 1.0f - 0.000013f,
    0.668104f, 1.0f - 0.000013f,
    0.667979f, 1.0f - 0.335851f,
    0.000059f, 1.0f - 0.000004f,
    0.335973f, 1.0f - 0.335903f,
    0.336098f, 1.0f - 0.000071f,
    0.667979f, 1.0f - 0.335851f,
    0.335973f, 1.0f - 0.335903f,
    0.336024f, 1.0f - 0.671877f,
    1.000004f, 1.0f - 0.671847f,
    0.999958f, 1.0f - 0.336064f,
    0.667979f, 1.0f - 0.335851f,
    0.668104f, 1.0f - 0.000013f,
    0.335973f, 1.0f - 0.335903f,
    0.667979f, 1.0f - 0.335851f,
    0.335973f, 1.0f - 0.335903f,
    0.668104f, 1.0f - 0.000013f,
    0.336098f, 1.0f - 0.000071f,
    0.000103f, 1.0f - 0.336048f,
    0.000004f, 1.0f - 0.671870f,
    0.336024f, 1.0f - 0.671877f,
    0.000103f, 1.0f - 0.336048f,
    0.336024f, 1.0f - 0.671877f,
    0.335973f, 1.0f - 0.335903f,
    0.667969f, 1.0f - 0.671889f,
    1.000004f, 1.0f - 0.671847f,
    0.667979f, 1.0f - 0.335851f
};

static const GLfloat triangle_vertex_data[] = {
    -1.0f,
    -1.0f,
    0.0f,
    1.0f,
    -1.0f,
    0.0f,
    0.0f,
    1.0f,
    0.0f,
};

static const GLfloat cube_vertex_data[] = {
    -1.0f, -1.0f, -1.0f, // triangle 1 : begin
    -1.0f, -1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f, // triangle 1 : end
    1.0f, 1.0f, -1.0f, // triangle 2 : begin
    -1.0f, -1.0f, -1.0f,
    -1.0f, 1.0f, -1.0f, // triangle 2 : end
    1.0f, -1.0f, 1.0f,
    -1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, 1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, -1.0f,
    1.0f, -1.0f, 1.0f,
    -1.0f, -1.0f, 1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, -1.0f, 1.0f,
    1.0f, -1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, 1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, -1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, -1.0f,
    -1.0f, 1.0f, -1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, -1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, -1.0f, 1.0f
};

void NIP_Engine::Window::Initialise(const char* title, int w, int h)
{
    // Pass window variables
    width = w;
    height = h;

    // Create main camera
    mainCamera = new Camera(this);

    // Check if GLFW is working
    if (!glfwInit()) {
        NE_LOG_ERROR("Failed to initialize GLFW\n");
    }

    // GLFW hints
    glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
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

    // Generate VAO buffer
    glGenVertexArrays(1, &VAO);

    // Generate vertex buffer
    glGenBuffers(1, &vertexbuffer); // Generate 1 buffer, put the resulting identifier in vertexbuffer

    // Generate uv buffer
    glGenBuffers(1, &uvbuffer); // Generate 1 buffer, put the resulting identifier in vertexbuffer

    // Load debug shaders
    programID
        = LoadShaders("../../NIP_Engine/Shaders/debug.vert", "../../NIP_Engine/Shaders/debug.frag");

    // Load debug texture
    LoadBMPFromFile("../../NIP_Engine/Textures/debug_uv.bmp");

    // Texture filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    // Bind VAO
    glBindVertexArray(VAO);

    // Bind vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer); // Bind vertex buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertex_data), cube_vertex_data, GL_STATIC_DRAW); // Give our vertices to OpenGL.

    glVertexAttribPointer(
        0, // attribute 0. No particular reason for 0, but must match the layout in the shader.
        3, // size
        GL_FLOAT, // type
        GL_FALSE, // normalized?
        0, // stride
        (void*)0 // array buffer offset
    );

    glBindBuffer(GL_ARRAY_BUFFER, uvbuffer); // Bind uv buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_uv_data), cube_uv_data, GL_STATIC_DRAW); // Give our uvs to OpenGL.

    glVertexAttribPointer(
        1, // attribute 0. No particular reason for 0, but must match the layout in the shader.
        2, // size
        GL_FLOAT, // type
        GL_FALSE, // normalized?
        0, // stride
        (void*)0 // array buffer offset
    );

    // Enable vertex attributes
    glEnableVertexAttribArray(0); // Vertex position
    glEnableVertexAttribArray(1); // UVs

    // Setup Done
    isRunning = true;
}

NIP_Engine::Camera::Camera(Window* win)
{
    boundedWindow = win;
}
void NIP_Engine::Camera::PassUserInput(double* mouse_x, double* mouse_y, bool forward, bool backward, bool left, bool right)
{
    // Called on update

    // Mouselook
    int window_w, window_h;
    boundedWindow->GetWindowDimension(&window_w, &window_h);
    horizontalAngle += lookSpeed * NE_DELTATIME * float(window_w / 2 - *mouse_x);
    verticalAngle += lookSpeed * NE_DELTATIME * float(window_h / 2 - *mouse_y);

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
}

void NIP_Engine::Window::GetWindowDimension(int* w, int* h)
{
    *w = width;
    *h = height;
}

void NIP_Engine::Camera::CalculatePerspective(glm::mat4* projection)
{
    // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
    int w, h;
    boundedWindow->GetWindowDimension(&w, &h);
    glm::mat4 calculatedProjection = glm::perspective(glm::radians(fieldOfView), (float)w / (float)h, 0.1f, 100.0f);

    // Camera matrix
    glm::mat4 View = glm::lookAt(
        position, // Camera is at (4,3,3), in World Space
        position + dir_forward, // and looks at the origin
        dir_up // Head is up (set to 0,-1,0 to look upside-down)
    );

    // Model matrix : an identity matrix (model will be at the origin)
    glm::mat4 Model = glm::mat4(1.0f);

    // Our ModelViewProjection : multiplication of our 3 matrices
    *projection = calculatedProjection * View * Model; // Remember, matrix multiplication is the other way around
}

double xpos, ypos;
bool m_forward, m_back, m_left, m_right;
void NIP_Engine::Window::Update()
{
    // Tick
    tick++;

    // Handle events
    glfwPollEvents();

    // Grab cursor events
    glfwGetCursorPos(win, &xpos, &ypos);
    glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPos(win, width / 2, height / 2);

    // Pass input events to camera
    mainCamera->PassUserInput(&xpos, &ypos, (glfwGetKey(win, GLFW_KEY_W) == GLFW_PRESS), (glfwGetKey(win, GLFW_KEY_S) == GLFW_PRESS), (glfwGetKey(win, GLFW_KEY_A) == GLFW_PRESS), (glfwGetKey(win, GLFW_KEY_D) == GLFW_PRESS));

    // Calculate Perspective
    mainCamera->CalculatePerspective(&mvp);

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

    // Bind VAO
    glBindVertexArray(VAO);

    // Use generated shader program
    glUseProgram(programID);

    // Pass matrix to vertex shader
    GLuint MatrixID = glGetUniformLocation(programID, "MVP");
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);

    // Draw cube
    glDrawArrays(GL_TRIANGLES, 0, 12 * 3); // 12 triangles * 3 vertices each

    // Unbind VAO
    glBindVertexArray(0);

    // Swap buffers
    glfwSwapBuffers(win);
}

// Clean
void NIP_Engine::Window::Clean()
{
    NE_LOG_INFO("Window Cleaned!\n");
}

GLuint NIP_Engine::Window::LoadShaders(const char* vertex_path, const char* frag_path)
{
    // Create the shaders
    GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    // Read the Vertex Shader code from the file
    std::string VertexShaderCode;
    std::ifstream VertexShaderStream(vertex_path, std::ios::in);
    if (VertexShaderStream.is_open()) {
        std::stringstream sstr;
        sstr << VertexShaderStream.rdbuf();
        VertexShaderCode = sstr.str();
        VertexShaderStream.close();
    } else {

        NE_LOG_ERROR("Error loading vertex shader: %s", std::strerror(errno));
        getchar();
        return 0;
    }

    // Read the Fragment Shader code from the file
    std::string FragmentShaderCode;
    std::ifstream FragmentShaderStream(frag_path, std::ios::in);
    if (FragmentShaderStream.is_open()) {
        std::stringstream sstr;
        sstr << FragmentShaderStream.rdbuf();
        FragmentShaderCode = sstr.str();
        FragmentShaderStream.close();
    }
    /* 	else {

            NE_LOG_ERROR("Error loading shader: %s", std::strerror(errno));
            getchar();
            return 0;
        } */

    GLint Result = GL_FALSE;
    int InfoLogLength;

    // Compile Vertex Shader
    NE_LOG_INFO("Compiling vertex shader : %s\n", vertex_path);
    char const* VertexSourcePointer = VertexShaderCode.c_str();
    glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
    glCompileShader(VertexShaderID);

    // Check Vertex Shader
    glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0) {
        std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
        glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
        NE_LOG_ERROR("%s\n", &VertexShaderErrorMessage[0]);
    }

    // Compile Fragment Shader
    NE_LOG_INFO("Compiling frag shader : %s\n", frag_path);
    char const* FragmentSourcePointer = FragmentShaderCode.c_str();
    glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
    glCompileShader(FragmentShaderID);

    // Check Fragment Shader
    glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0) {
        std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
        glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
        NE_LOG_ERROR("%s\n", &FragmentShaderErrorMessage[0]);
    }

    // Link the program
    NE_LOG_INFO("Linking generated program\n");
    GLuint ProgramID = glCreateProgram();
    glAttachShader(ProgramID, VertexShaderID);
    glAttachShader(ProgramID, FragmentShaderID);
    glLinkProgram(ProgramID);

    // Check the program
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0) {
        std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
        glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
        NE_LOG_ERROR("%s\n", &ProgramErrorMessage[0]);
    }

    glDetachShader(ProgramID, VertexShaderID);
    glDetachShader(ProgramID, FragmentShaderID);

    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);

    NE_LOG_INFO("Done!\n");

    return ProgramID;
}
