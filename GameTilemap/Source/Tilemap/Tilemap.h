#pragma once


class SpriteSheet;


class Tilemap
{
public:
    enum class TileType
    {
        Floor,
        Wall,
        NumTypes,
        Table
    };

    struct TileProperties
    {
        //       fw::Texture* m_pTexture;
        //    OR string m_SpriteName;      
        //    OR vec2 m_UVScale, m_UVOffset; 
        //    OR SpriteInfo* m_SpriteInfo;
        bool m_Walkable;
    };

public:
    Tilemap(TileType* pLayout, int width, int height);

    void Draw();

protected:
    fw::Mesh* m_pTileMesh;
    SpriteSheet* m_pSpriteSheet;

    TileType* m_pLayout;



    vec2 m_MapSize = vec2(0, 0); // Width and Height of the map in tiles.
    vec2 m_TileSize = vec2(5, 5); // How big is a tile in world units?

    //vec2 m_Position; // World position.
    //ivec2 m_TilePos; // Position of a tile in tile space.
    //int m_TileIndex; // Index into the layout array of the tile.




    //TileProperties m_Properties[(int)TileType::NumTypes];
    std::vector<TileProperties> m_Properties;
};
