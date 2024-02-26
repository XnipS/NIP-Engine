#include "Entity.h"
#include "EntityTransform.h"

NIP_Engine::Transform* NIP_Engine::EntityTransform::GetTransform(int owner)
{
    for (int i = 0; i < transforms.size(); i++) {
        if (transforms[i].ownerID == owner) {
            return &transforms[i];
        }
    }
    return nullptr;
}

NIP_Engine::Transform* NIP_Engine::EntityTransform::CreateTransform(int owner)
{
    Transform newObject = Transform();
    newObject.ownerID = owner;
    transforms.push_back(newObject);
    return &transforms.back();
}

void NIP_Engine::Transform::Start()
{
}

void NIP_Engine::Transform::Update()
{
}