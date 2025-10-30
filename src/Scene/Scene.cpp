#include "Scene.h"

void Scene::AddObject(GameObject* obj) {
    m_Objects.push_back(obj);
}

void Scene::RemoveObject(GameObject* obj) {
    m_Objects.erase(std::find(m_Objects.begin(), m_Objects.end(), obj));
}

