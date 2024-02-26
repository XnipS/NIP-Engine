#pragma once
#include "Entity.h"
namespace NIP_Engine {

class Transform : public Component {
public:
    void Start() override;

    void Update() override;

    glm::mat4* GetModelMatrix()
    {
        return &modelMatrix;
    }

private:
    glm::mat4 modelMatrix = glm::mat4(1.0f);
};

class EntityTransform {
public:
    void Start()
    {
        for (int i = 0; i < transforms.size(); i++) {
            transforms[i].Start();
        }
    }
    void Update()
    {
        for (int i = 0; i < transforms.size(); i++) {
            transforms[i].Update();
        }
    }
    Transform* CreateTransform(int owner);
    Transform* GetTransform(int owner);
    std::vector<Transform> transforms;

private:
};
}