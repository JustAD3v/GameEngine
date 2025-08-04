#include "MapParser.h"

MapParser* MapParser::s_Instance = nullptr;

bool MapParser::Load() {
    // return Parse("MAP", "assets/maps/map");
}

void MapParser::Clean() {
    std::map<std::string, GameMap*>::iterator it;
    for(it = m_MapDict.begin(); it != m_MapDict.end(); it++) {
        it->second = nullptr;
    }
    m_MapDict.clear();
}
