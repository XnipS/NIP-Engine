#pragma once

#include "Entity.h"
#include <cstddef>
#include <glm/fwd.hpp>
#include <vector>
namespace NIP_Engine {

class MeshRenderer : public Component {
public:
    void Start() override;

    void UpdateRenderer(NIP_Engine::EntitySystem* sys);

    void LinkMatrices(glm::mat4* mvpmatrix, glm::mat4* vmatrix)
    {
        mvp = mvpmatrix;
        viewMatrix = vmatrix;
    }
    char* modelPath = "../../NIP_Engine/Models/sphere.obj";

private:
    // Shader program
    GLuint programID;
    // Vertex array object
    GLuint VAO;
    // Texture TODO
    // GLuint textureID;

    // Buffers
    GLuint vertexbuffer;
    GLuint uvbuffer;
    GLuint normalbuffer;
    GLuint indexbuffer;

    // Pass to vertex shader
    GLuint MVPID;
    GLuint ModelMatrixID;
    GLuint ViewMatrixID;
    GLuint LightPosID;

    // Pointers
    glm::mat4* mvp = nullptr;
    glm::mat4* viewMatrix = nullptr;

    glm::vec3 lightPosition = glm::vec3(5, 5, 5);
    std::vector<unsigned int> vertexIndices;
};

class EntityRenderer {
public:
    void Start()
    {
        for (int i = 0; i < renderers.size(); i++) {
            renderers[i].Start();
        }
    }
    void Update(NIP_Engine::EntitySystem* sys)
    {
        for (int i = 0; i < renderers.size(); i++) {
            renderers[i].UpdateRenderer(sys);
        }
    }
    MeshRenderer* CreateMeshRenderer(int owner);
    MeshRenderer* GetMeshRenderer(int owner);
    std::vector<MeshRenderer> renderers;

private:
};
}