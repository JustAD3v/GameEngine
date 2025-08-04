#include "TileLayer.h"
#include "TextureManager.h"

TileLayer::TileLayer(int tilesize, int rowcount, int colcount, TileMap tilemap, TilesetList tilesets): m_Tilesets(tilesets) {
    m_RowCount = rowcount;
    m_ColCount = colcount;
    m_Tilemap = tilemap;
    m_TileSize = tilesize;

    for (int i = 0; i < m_Tilesets.size(); i++) {
        TextureManager::GetInstance()->Load(m_Tilesets[i].Name, "assets/maps" + m_Tilesets[i].Source);
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
                int tileSetIndex = tileID/1000 - 1; //tileID has this format : (tileSetID)(tileIDOnTileset), -1 to get back to index 0
                int tileIDOnTileset = tileID - 1000*(tileSetIndex+1);
                
                Tileset ts = m_Tilesets[tileSetIndex];
                int tileRow = tileIDOnTileset/ts.ColCount; 
                int tileCol = tileIDOnTileset - (tileRow*ts.ColCount);

                TextureManager::GetInstance()->DrawTile(ts.Name, j*ts.TileSize, i*ts.TileSize, ts.TileSize, tileRow, tileCol);
            }
        } 
    }
}

void TileLayer::Update() {

}