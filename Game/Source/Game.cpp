#include "Framework.h"

#include "Game.h"



Game::Game(fw::FWCore* pFrawework) : fw::GameCore(pFrawework)
{
  
}

Game::~Game()
{
    delete m_pShader;
    delete m_pMeshHuman;
    delete m_pMeshAnimal;

    for( fw::GameObject* pObject : m_Objects )
    {
        delete pObject;
    }
}

void Game::Init()
{
 
    m_GUIMANAGER = new fw::ImGuiManager(m_pFramework);
    m_GUIMANAGER->Init();

	
    m_pShader = new fw::ShaderProgram( "Data/Basic.vert", "Data/Basic.frag" );

    // Define our triangle as 3 positions.
    float attribsHuman[] =
    {
        0.0f,  0.0f, // Center
        0.5f,  0.5f, // Top right
        0.5f,  0.0f, // Right center
        0.5f, -0.5f, // Right bottom
    };

    m_pMeshHuman = new fw::Mesh();
    m_pMeshHuman->CreateShape( GL_POINTS, 4, &attribsHuman[0] );

    float attribsAnimal[] =
    {
        -0.0f,  0.0f, // Center
        -0.5f,  0.5f, // Top right
        -0.5f,  0.0f, // Right center
        -0.5f, -0.5f, // Right bottom
    };

    m_pMeshAnimal = new fw::Mesh( GL_LINES, 4, &attribsAnimal[0] );

    m_Objects.push_back( new fw::GameObject( 0.0f,  0.0f, m_pMeshHuman,  m_pShader ) );
    m_Objects.push_back( new fw::GameObject( 0.0f, -0.2f, m_pMeshAnimal, m_pShader ) );
    m_Objects.push_back( new fw::GameObject( 0.5f,  0.0f, m_pMeshAnimal, m_pShader ) );
}

void Game::Update(float delta)
{
    m_GUIMANAGER->StartFrame(delta);
    ImGui::ShowDemoWindow();
}

void Game::Draw()


{

    glClearColor( 0, 1, 0, 0 );
    glClear( GL_COLOR_BUFFER_BIT );

    glPointSize( 10 );
    
    for( fw::GameObject* pObject : m_Objects )
    {
        pObject->Draw();
    }
    m_GUIMANAGER->EndFrame();
}
