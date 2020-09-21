#include "Framework.h"

#include "Game.h"

Game::Game()
{
}

Game::~Game()
{
}

void Game::Init()
{
    m_pShader = new fw::ShaderProgram( "Data/Basic.vert", "Data/Basic.frag" );

    m_pMesh = new fw::Mesh(1);
    m_pMesh2 = new fw::Mesh(2);

	
}

void Game::Update()
{
}

void Game::Draw()
{
    glClearColor( 0, 1, 0, 0 );
    glClear( GL_COLOR_BUFFER_BIT );

    glPointSize( 10 );
    glUseProgram( m_pShader->GetProgram() );
    m_pMesh->Draw(0, 0, m_pShader);
    m_pMesh2->Draw(0, 0, m_pShader);
	
}
