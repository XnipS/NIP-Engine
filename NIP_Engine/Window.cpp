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
GLuint VertexArrayID; // VAO
GLuint vertexbuffer;
GLuint programID; // Shader program for triangle
glm::mat4 mvp; // View matrix

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

    glEnable(GL_DEPTH_TEST); // Enable depth test
    glDepthFunc(GL_LESS); // Accept fragment if it closer to the camera than the former one

    // Open a window and create a OpenGL context
    win = glfwCreateWindow(w, h, title, glfwGetPrimaryMonitor(), NULL);
    if (win == NULL) {
        NE_LOG_ERROR("Failed to open GLFW window\n");
        glfwTerminate();
    }

    // Initialise GLEW
    glfwMakeContextCurrent(win);
    glewExperimental = true;
    glewInit();

    // Bind VAO
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    glGenBuffers(1, &vertexbuffer); // Generate 1 buffer, put the resulting identifier in vertexbuffer
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer); // Bind vertex buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertex_data), cube_vertex_data, GL_STATIC_DRAW); // Give our vertices to OpenGL.

    // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
    glm::mat4 Projection = glm::perspective(glm::radians(45.0f), (float)w / (float)h, 0.1f, 100.0f);

    // Camera matrix
    glm::mat4 View = glm::lookAt(
        glm::vec3(4, 3, 3), // Camera is at (4,3,3), in World Space
        glm::vec3(0, 0, 0), // and looks at the origin
        glm::vec3(0, 1, 0) // Head is up (set to 0,-1,0 to look upside-down)
    );

    // Model matrix : an identity matrix (model will be at the origin)
    glm::mat4 Model = glm::mat4(1.0f);

    // Our ModelViewProjection : multiplication of our 3 matrices
    mvp = Projection * View * Model; // Remember, matrix multiplication is the other way around

    // Load debug shaders
    programID = LoadShaders("../../NIP_Engine/Shaders/debug.vert", "../../NIP_Engine/Shaders/debug.frag");

    // Setup Done
    isRunning = true;
}

void NIP_Engine::Window::Update()
{
    // Tick
    tick++;

    // Handle events
    glfwPollEvents();

    // Check if should close
    if (glfwWindowShouldClose(win)) {
        isRunning = false;
    }
}

void NIP_Engine::Window::Render()
{
    // Clear
    glClearColor(0.5, 0.5, 1.0, 1.0); // Set clear colour
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear

    // Pass matrix to vertex shader
    GLuint MatrixID = glGetUniformLocation(programID, "MVP");
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);

    // Render
    glEnableVertexAttribArray(0); // Start of VAO
    // glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer); // Bind vertex (Dont need this?)
    glVertexAttribPointer(
        0, // attribute 0. No particular reason for 0, but must match the layout in the shader.
        3, // size
        GL_FLOAT, // type
        GL_FALSE, // normalized?
        0, // stride
        (void*)0 // array buffer offset
    );
    // Draw the triangle
    glUseProgram(programID); // Use shader program
    // glDrawArrays(GL_TRIANGLES, 0, 3); // 3 vertices total -> 1 triangle
    glDrawArrays(GL_TRIANGLES, 0, 12 * 3); // 12 triangles * 3 vertices each
    glDisableVertexAttribArray(0); // End of VAO

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