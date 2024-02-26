#pragma once

#include <GL/glew.h>
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <iostream>
#include <memory>
#include <type_traits>
#include <typeinfo>
#include <vector>
namespace NIP_Engine {

class Component {
public:
    virtual void Start() {};
    virtual void Update() {};
    int ownerID;
};

class Entity {
public:
    Entity(int myID)
    {
        objectID = myID;
    }

    inline int GetObjectID()
    {
        return objectID;
    }

private:
    int objectID;
};

class EntitySystem {
public:
    // Create/Destroy
    Entity CreateGameObject();
    void DestroyGameObject(int ID);
    Entity* GetObject(int ID);

private:
    std::vector<Entity> entities;
    int currentID = 10;
};
}