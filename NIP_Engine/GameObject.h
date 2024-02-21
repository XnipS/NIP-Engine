#pragma once

#include <cmath>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <vector>
namespace NIP_Engine {

class Component {
public:
    virtual void Start();
    virtual void Update();
};

class Transform : Component {
public:
    glm::vec3 position = glm::vec3(0.0, 0.0, 0.0);

    void Start() override
    {
        // Start transform logic
    }

    void Update() override
    {
        // Update transform logic
    }
};

class MeshRenderer : Component {
public:
    void Start() override;

    void Update() override;
};

class GameObject {
public:
    GameObject(int myID)
    {
        objectID = myID;
    }
    inline int GetObjectID()
    {
        return objectID;
    }
    void Start()
    {
        for (Component* component : components) {
            component->Start();
        }
    }
    void Update()
    {
        for (Component* component : components) {
            component->Update();
        }
    }
    void AddComponent(Component newComp)
    {
        components.push_back(&newComp);
    }

private:
    std::vector<Component*> components;
    int objectID;
};

class GameObjectManager {
public:
    void UpdateGameObjects();

    // Create/Destroy
    GameObject CreateGameObject();
    void DestroyGameObject(int ID);

private:
    std::vector<GameObject*> GameObjects;
    int currentID = 10;
};
}