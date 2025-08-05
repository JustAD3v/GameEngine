#ifndef TILELAYER_H
#define TILELAYER_H

#include "Layer.h"
#include <string>
#include <vector>
#include <iostream>

struct Tileset {
    int firstID, lastID;
    int RowCount, ColCount;
    int TileCount, TileSize;
    std::string Name, Source;
};

using TilesetList = std::vector<Tileset>;
using TileMap = std::vector<std::vector<int>>;

class TileLayer : public Layer {

    public:
        TileLayer(int tilesize, int rowcount, int colcount, TileMap tilemap, TilesetList tilesets);
        virtual void Render();
        virtual void Update();
        inline TileMap GetTilemap() {return m_Tilemap;}
        int GetTilesetID(int tileID);

    private:
        int m_TileSize;
        int m_RowCount, m_ColCount;
        TileMap m_Tilemap;
        TilesetList m_Tilesets;
};

#endif