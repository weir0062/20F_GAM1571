#include "GamePCH.h"

#include "Game.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    fw::FWCore* pFramework = new fw::FWCore();
    pFramework->Init( 600, 600 );

    vec2 a(5, 5);
    vec2 b(2, 2);
    vec2 c(7, 7);
    //assert(a += 2 == c );
    Game* pGame = new Game( pFramework );
    pGame->Init();

    pFramework->Run( pGame );
    pFramework->Shutdown();

    delete pGame;
    delete pFramework;
}
