#include "EntityRenderer.h"
#include "BMP_Loader.h"
#include "OBJ_Loader.h"
#include "Shader_Loader.h"

NIP_Engine::MeshRenderer* NIP_Engine::EntityRenderer::CreateMeshRenderer(int owner)
{
    MeshRenderer newObject = MeshRenderer();
    newObject.ownerID = owner;
    renderers.push_back(newObject);
    // newObject.Start();
    return &renderers.back();
}

// Mesh Renderer
void NIP_Engine::MeshRenderer::Start()
{
    // Generate vertex buffer
    glGenBuffers(1, &vertexbuffer); // Generate 1 buffer, put the resulting identifier in vertexbuffer

    // Generate uv buffer
    glGenBuffers(1, &uvbuffer); // Generate 1 buffer, put the resulting identifier in vertexbuffer

    // Load debug shaders
    programID
        = LoadShaders("../../NIP_Engine/Shaders/debug.vert", "../../NIP_Engine/Shaders/debug.frag");

    // Load debug texture
    LoadBMPFromFile("../../NIP_Engine/Textures/debug_uv.bmp");

    // Load debug model
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> uvs;
    std::vector<glm::vec3> normals; // Won't be used at the moment.
    LoadOBJFromFile("../../NIP_Engine/Models/debug.obj", &vertices, &uvs, &normals);

    // Bind vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer); // Bind vertex buffer
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW); // Give our vertices to OpenGL.

    glVertexAttribPointer(
        0, // attribute 0. No particular reason for 0, but must match the layout in the shader.
        3, // size
        GL_FLOAT, // type
        GL_FALSE, // normalized?
        0, // stride
        (void*)0 // array buffer offset
    );

    glBindBuffer(GL_ARRAY_BUFFER, uvbuffer); // Bind uv buffer
    glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW); // Give our uvs to OpenGL.

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
}

void NIP_Engine::MeshRenderer::Update()
{
    // Use generated shader program
    glUseProgram(programID);

    // Pass matrix to vertex shader
    GLuint MatrixID = glGetUniformLocation(programID, "MVP");
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &(*mvp)[0][0]);

    // Draw cube
    glDrawArrays(GL_TRIANGLES, 0, 12 * 3); // 12 triangles * 3 vertices each
}