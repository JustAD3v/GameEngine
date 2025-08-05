#ifndef MAPPARSER_H
#define MAPPARSER_H

#include <map>
#include <string>
#include "GameMap.h"
#include "TileLayer.h"
#include "json.hpp" 
#include <iostream>
#include <fstream>

using json = nlohmann::json;

class MapParser {
    public:
        inline bool Load(std::string id, std::string source) {return Parse(id, source);}
        void Clean();
        
        inline GameMap* GetMap(std::string id) {return m_MapDict[id];}
        inline static MapParser* GetInstance() {return s_Instance = (s_Instance != nullptr) ? s_Instance : new MapParser();}

    private:
        bool Parse(std::string id, std::string source);
        Tileset ParseTileset(json Jtileset);
        TileLayer* ParseTileLayer(json Jtilelayer, int tilesize, int rowcount, int colcount, TilesetList tilesets);

    private:
        MapParser() {};
        static MapParser* s_Instance;
        std::map<std::string, GameMap*> m_MapDict;
};

#endif