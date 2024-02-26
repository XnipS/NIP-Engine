#include "Entity.h"
#include <cstddef>

NIP_Engine::Entity NIP_Engine::EntitySystem::CreateGameObject()
{
    Entity newObject = Entity(currentID);
    currentID++;
    entities.push_back(newObject);
    return newObject;
}
void NIP_Engine::EntitySystem::DestroyGameObject(int ID)
{
    std::vector<Entity>::iterator iterator;
    for (int i = 0; i < entities.size(); i++) {
        if (entities[i].GetObjectID() == ID) {
            iterator = entities.begin() + i;
            entities.erase(iterator);
        }
    }
}
NIP_Engine::Entity* NIP_Engine::EntitySystem::GetObject(int ID)
{
    for (int i = 0; i < entities.size(); i++) {
        if (entities[i].GetObjectID() == ID) {
            return &entities[i];
        }
    }
    return nullptr;
}
