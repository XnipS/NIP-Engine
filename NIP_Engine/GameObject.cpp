#include "GameObject.h"

void NIP_Engine::GameObjectManager::UpdateGameObjects()
{
    for (int i = 0; i < GameObjects.size(); i++) {
        GameObjects[i]->Update();
    }
}

NIP_Engine::GameObject NIP_Engine::GameObjectManager::CreateGameObject()
{
    GameObject newObject = GameObject(currentID);
    currentID++;
    GameObjects.push_back(&newObject);
    newObject.Start();
    return newObject;
}
void NIP_Engine::GameObjectManager::DestroyGameObject(int ID)
{
    std::vector<GameObject*>::iterator iterator;
    for (int i = 0; i < GameObjects.size(); i++) {
        if (GameObjects[i]->GetObjectID() == ID) {
            iterator = GameObjects.begin() + i;
            GameObjects.erase(iterator);
        }
    }
}
// Mesh Renderer
void NIP_Engine::MeshRenderer::Start()
{
}

void NIP_Engine::MeshRenderer::Update()
{
}
