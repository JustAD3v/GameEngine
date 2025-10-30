#include "MapParser.h"

MapParser* MapParser::s_Instance = nullptr;

bool MapParser::Parse(std::string id, std::string source) {
    std::ifstream file(source);
    if (!file.is_open()) {
        std::cerr << "Erreur : impossible d'ouvrir le fichier JSON.\n";
        return false;
    }
    json JMap;
    try {
        file >> JMap; 
    } catch (json::parse_error& e) {
        std::cerr << "Erreur de parsing JSON : " << e.what() << '\n';
        return false;
    }

    TilesetList tilesetsL;
    if (JMap.contains("tilesets")) {
        for (const auto& tileset : JMap["tilesets"]) {
            tilesetsL.push_back(ParseTileset(tileset));
        }
    }

    GameMap* gamemap = new GameMap();
    if (JMap.contains("layers")) {
        int tilesize = JMap["tilewidth"].get<int>();
        for (const auto& layer : JMap["layers"]) {
            int rowcount = layer["height"].get<int>(); //get = méthode de json pour convertir explicitement le type. 
            int colcount = layer["width"].get<int>();
            gamemap->m_MapLayers.push_back(ParseTileLayer(layer, tilesize, rowcount, colcount, tilesetsL));
        }
    }

    m_MapDict[id] = gamemap;
    return true;
}

Tileset MapParser::ParseTileset(json Jtileset) {
    Tileset tileset;
    tileset.Name = Jtileset["name"].get<std::string>(); 
    tileset.firstID = Jtileset["firstgid"].get<int>();
    tileset.lastID = tileset.firstID + Jtileset["tilecount"].get<int>() - 1;
    tileset.TileCount = Jtileset["tilecount"].get<int>();
    tileset.TileSize = Jtileset["tilewidth"].get<int>();
    tileset.ColCount = Jtileset["columns"].get<int>();
    tileset.RowCount = tileset.TileCount/tileset.ColCount;
    tileset.Source = Jtileset["image"].get<std::string>();
    return tileset;
}

TileLayer* MapParser::ParseTileLayer(json Jtilelayer, int tilesize, int rowcount, int colcount, TilesetList tilesets) {
    TileMap tilemap(rowcount, std::vector<int>(colcount, 0));
    int index = 0;
    for(int i = 0; i < rowcount; i++) {
        for(int j = 0; j < colcount; j++) {
            tilemap[i][j] = Jtilelayer["data"][index].get<int>();
            //std::cout << i << ", " << j << " : " << tilemap[i][j] << std::endl;
            index++;
        }
    }
    return (new TileLayer(tilesize, rowcount, colcount, tilemap, tilesets));
}

void MapParser::Clean() {
    for (auto it = m_MapDict.begin(); it != m_MapDict.end(); ++it) {
        delete it->second;       // delete l'objet GameMap et tout ce qu'il contient
        it->second = nullptr;
    }
    m_MapDict.clear();
}

void MapParser::DestroyInstance() {
    if (s_Instance) {
        delete s_Instance;
        s_Instance = nullptr;
    }
}
