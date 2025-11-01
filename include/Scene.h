#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include "GameObject.h"

class Scene {
    public:
        Scene(std::string SceneID) : m_SceneID(SceneID) {};
        void AddObject(std::string ObjectID, GameObject* obj);
        GameObject *getObjectById(std::string ObjectId);
        void RemoveObject(std::string ObjectID);
        void Clean();

    private:
        std::map<std::string, GameObject*> m_ObjectsMap;
        std::vector<GameObject*> m_CollidingObjects;
        std::string m_SceneID;
};
#endif
