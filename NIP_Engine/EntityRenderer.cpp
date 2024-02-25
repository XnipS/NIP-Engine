#include "EntityRenderer.h"
#include "BMP_Loader.h"
#include "OBJ_Loader.h"
#include "Shader_Loader.h"
#include <glm/fwd.hpp>

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
    // Generate buffers
    glGenBuffers(1, &vertexbuffer); // Generate 1 buffer, put the resulting identifier in vertexbuffer
    glGenBuffers(1, &uvbuffer);
    glGenBuffers(1, &normalbuffer);
    glGenBuffers(1, &indexbuffer);

    // Load debug shaders
    programID
        = LoadShaders("../../NIP_Engine/Shaders/debug.vert", "../../NIP_Engine/Shaders/debug.frag");

    // Load debug texture
    LoadBMPFromFile("../../NIP_Engine/Textures/debug_uv.bmp");

    // Load debug model
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> uvs;
    std::vector<glm::vec3> normals; // Won't be used at the moment.

    OBJ_Loader::LoadOBJFromFileIndexed("../../NIP_Engine/Models/sphere.obj", &vertices, &uvs, &normals, &vertexIndices);

    // VERTEX BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind vertex buffer

    // UV BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
    glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind UV buffer

    // NORMAL BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind normal buffer

    // INDEX BUFFER
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertexIndices.size() * sizeof(unsigned int), &vertexIndices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind vertex index buffer

    // Use generated shader program
    glUseProgram(programID);

    // Pass data to shader uniforms
    MVPID = glGetUniformLocation(programID, "MVP");
    ModelMatrixID = glGetUniformLocation(programID, "M");
    ViewMatrixID = glGetUniformLocation(programID, "V");
    LightPosID = glGetUniformLocation(programID, "LightPosition_worldspace");
}

void NIP_Engine::MeshRenderer::Update()
{

    // Pass matrix to vertex shader
    glUniformMatrix4fv(MVPID, 1, GL_FALSE, &(*mvp)[0][0]);

    // Pass model matrix to vertex shader
    glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &(*modelMatrix)[0][0]);

    // Pass view matrix to vertex shader
    glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &(*viewMatrix)[0][0]);

    // Pass light position to vertex shader
    glUniform3f(LightPosID, lightPosition.x, lightPosition.y, lightPosition.z);

    // Draw cube
    glDrawElements(GL_TRIANGLES, vertexIndices.size(), GL_UNSIGNED_INT, (void*)0);
}