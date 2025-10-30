#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <map>
#include <string>
#include "GameObject.h"

class Scene {
    public:
        void AddObject(GameObject* obj);
        GameObject *getObjectById(std::string ObjectId);
        void RemoveObject(GameObject* obj);

    private:
        std::vector<GameObject*> m_Objects;
        std::map<std::string, GameObject*> m_ObjectsMap;
        std::vector<GameObject*> m_CollidingObjects;
        std::map<std::string, GameObject*> m_CollidingObjectsMap;
};

#endif