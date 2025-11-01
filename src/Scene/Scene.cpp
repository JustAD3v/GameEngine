#include "Scene.h"

void Scene::AddObject(std::string ObjectID, GameObject* obj) {
    obj->setScene(this);
    m_ObjectsMap.insert({ObjectID, obj}); // insert does nothing if the key already exists !
    if (obj->getCollider() != nullptr && obj->getCollider()->isSolid()) {
        m_CollidingObjects.push_back(obj);
    }
}

void Scene::RemoveObject(std::string ObjectID) {
    auto it = m_ObjectsMap.find(ObjectID);
    if (it != m_ObjectsMap.end()) { //object found
        GameObject *removedObj = it->second;
        if (removedObj->getCollider() != nullptr && removedObj->getCollider()->isSolid()) {
            m_CollidingObjects.erase(std::find(m_CollidingObjects.begin(), m_CollidingObjects.end(), removedObj));
        }
        removedObj->setScene(nullptr);
        m_ObjectsMap.erase(ObjectID);
    }
    else std::cout << "Object with name : " << ObjectID << "not found" << std::endl;
    return;   
}

GameObject* Scene::getObjectById(std::string ObjectID) {
    auto it = m_ObjectsMap.find(ObjectID);
    if (it != m_ObjectsMap.end()) { //object found
        return it->second;
    }
    else std::cout << "Object with name : " << ObjectID << "not found (nullptr returned)" << std::endl;
    return nullptr;   
}

void Scene::Clean() {
    for (auto it = m_ObjectsMap.begin(); it != m_ObjectsMap.end(); it++) {
        RemoveObject(it->first);
    }
}
