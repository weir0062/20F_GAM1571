#include "GamePCH.h"

#include "Tilemap/Tilemap.h"
//#include "Tilemap/Layouts.h"

using TT = Tilemap::TileType;

const Tilemap::TileType level1Layout[] =
{
    TT::Wall, TT::Wall,  TT::Wall,
    TT::Wall, TT::Floor, TT::Wall,
    TT::Wall, TT::Wall,  TT::Wall,
};
