#pragma once

#include "Entity.h"
#include <glm/fwd.hpp>
#include <vector>
namespace NIP_Engine {

class MeshRenderer : public Component {
public:
    void Start() override;

    void Update() override;

    void LinkMatrices(glm::mat4* mvpmatrix, glm::mat4* mmatrix, glm::mat4* vmatrix)
    {
        mvp = mvpmatrix;
        modelMatrix = mmatrix;
        viewMatrix = vmatrix;
    }

private:
    // Shader program
    GLuint programID;
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
    glm::mat4* mvp;
    glm::mat4* modelMatrix;
    glm::mat4* viewMatrix;
    char* modelPath;

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
    void Update()
    {
        for (int i = 0; i < renderers.size(); i++) {
            renderers[i].Update();
        }
    }
    MeshRenderer* CreateMeshRenderer(int owner);
    std::vector<MeshRenderer> renderers;

private:
};
}