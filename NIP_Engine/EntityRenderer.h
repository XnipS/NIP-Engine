#pragma once

#include "Entity.h"
#include <vector>
namespace NIP_Engine {

class MeshRenderer : public Component {
public:
    void Start() override;

    void Update() override;

    void LinkMVP(glm::mat4* matrix)
    {
        mvp = matrix;
    }

private:
    GLuint programID; // Shader program
    GLuint vertexbuffer;
    GLuint uvbuffer;

    glm::mat4* mvp;
	char* modelPath;
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