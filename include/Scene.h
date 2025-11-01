#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <map>
#include <string>
#include "GameObject.h"

class Scene {
    public:
        void AddObject(std::string ObjectID, GameObject* obj);
        GameObject *getObjectById(std::string ObjectId);
        void RemoveObject(std::string ObjectID);

    private:
        std::map<std::string, GameObject*> m_ObjectsMap;
        std::vector<GameObject*> m_CollidingObjects;
};

#endif

