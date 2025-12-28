#include "Scene.h"
#include "Character.h"

void Scene::AddObject(std::string ObjectID, GameObject* obj) {
    obj->setScene(this);
    m_ObjectsMap.insert({ObjectID, obj}); // insert does nothing if the key already exists !
    if (obj->getCollider() != nullptr && obj->getCollider()->isSolid()) {
        m_CollidingObjects.push_back(obj);
    }
    if (obj->m_RigidBody) {
        // if object has a RigidBody then add it to the dynamic objects 
        m_DynamicObjects.push_back(obj);
    }
}

//Refactor since GameObject class befriends Scene class
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

std::ostream& operator<<(std::ostream& os, const Scene& s) {
    std::cout << "Scene (ID : " << s.m_SceneID << ") elements : " << std::endl;
    for (std::map<std::string, GameObject*>::const_iterator it = s.m_ObjectsMap.begin(); it != s.m_ObjectsMap.end(); ++it) {
        std::cout << "   " << it->first << " => " << *(it->second);
    };
    std::cout << "Elements with solide collider : " << std::endl;
    for (std::vector<GameObject*>::const_iterator it = s.m_CollidingObjects.begin(); it != s.m_CollidingObjects.end(); ++it) {
        std::cout << "   " << *(*it);
    }
    return os; 
}

void Scene::Update() {
    for (auto it = m_DynamicObjects.begin(); it != m_DynamicObjects.end(); ++it) {
        GameObject* curr_go = (*it);
        Vector2D old_pos = curr_go->m_Transform->GetPosition();
        curr_go->m_Transform->TranslateX(curr_go->m_RigidBody->GetPosition().x);
        //m_Transform->Translate(m_RigidBody->GetPosition());
    }
}

void Scene::Clean() { //destroys gameObjects so you can't reuse them in other scenes
    for (auto& pair : m_ObjectsMap) {
        if (pair.second) {
            pair.second->setScene(nullptr); 
            delete pair.second;            
        }
    }
    m_ObjectsMap.clear();
    m_CollidingObjects.clear();
}