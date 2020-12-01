 #include "GamePCH.h"
#include "Tilemap.h"
#include "Objects/SpriteSheet.h"

Tilemap::Tilemap(TileType* pLayout, int width, int height)
{
    // Setup all the tile properties.
    m_Properties.resize( (int)TileType::NumTypes );

    m_Properties[(int)TileType::Floor] = TileProperties( pGame->GetTexture("Floor"), true  );
    
    m_Properties[(int)TileType::Table] = TileProperties( "Blocks/block_02", false );
    
    m_pSpriteSheet->GetSpriteInfo( "Blocks/block_02" ).x/w, .y/h
    m_Properties[(int)TileType::Wall]  = TileProperties( uvScale, uvOffset,  false );
    
    m_Properties[(int)TileType::Wall]  = TileProperties(m_pSpriteSheet->GetSpriteInfo( "Blocks/block_02" ),  false );

    //m_Properties.push_back( TileProperties( "Floor", true  ) );
    //m_Properties.push_back( TileProperties( "Table", false ) );
    //m_Properties.push_back( TileProperties( "Wall",  false ) );

    // Allocate memory for m_pLayout.
    // Copy pLayout into m_pLayout.
}



void Tilemap::Draw()
{
    //for( y )
    for (int y = 0; y < m_Properties.size(); y++)

    {
        for(int x = 1; x < m_Properties.size(); x++)
        //int x = 1;
        {
            type = ??;
            pos = ??;
            shader = ??;
            texture = m_Properties[type].texture;

            mesh->draw( pos, shader, texture, uvscale, uvoffset );
        }
    }
}