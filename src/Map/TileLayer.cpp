#include "TileLayer.h"
#include "TextureManager.h"

TileLayer::TileLayer(int tilesize, int rowcount, int colcount, TileMap tilemap, TilesetList tilesets): m_Tilesets(tilesets) {
    m_RowCount = rowcount;
    m_ColCount = colcount;
    m_Tilemap = tilemap;
    m_TileSize = tilesize;

    for (size_t i = 0; i < m_Tilesets.size(); i++) {
        TextureManager::GetInstance()->Load(m_Tilesets[i].Name, "assets/maps/" + m_Tilesets[i].Source);
    }
}

void TileLayer::Render() {
    for(int i = 0; i < m_RowCount; i++){
        for (int j = 0; j < m_ColCount; j++) {
            int tileID = m_Tilemap[i][j];

            if (tileID == 0) {
                continue;
            }
            else {
                int tileSetIndex = GetTilesetID(tileID);  
                int tileIDOnTileset = tileID - m_Tilesets[tileSetIndex].firstID;
                // std::cout << "tileIDOnTileset: " << tileIDOnTileset << std::endl;

                Tileset ts = m_Tilesets[tileSetIndex];
                int tileRow = (tileIDOnTileset/ts.ColCount); 
                int tileCol = tileIDOnTileset - (tileRow*ts.ColCount);
                // std::cout << "row, col : " << tileRow << ", " << tileCol << std::endl;

                TextureManager::GetInstance()->DrawTile(ts.Name, j*ts.TileSize, i*ts.TileSize, ts.TileSize, tileRow, tileCol);
            }
        } 
    }
}

int TileLayer::GetTilesetID(int tileID) {
    int id = 0;
    while (tileID > m_Tilesets[id].lastID || tileID < m_Tilesets[id].firstID) {
        id += 1;
    }
    return id;
}

void TileLayer::Update() {

}