#include "GamePCH.h"

#include "Game.h"
#include "Objects/Player.h"
#include "Objects/PlayerController.h"
#include "Objects/Shapes.h"
#include "Events/GameEvents.h"

Game::Game(fw::FWCore* pFramework) : fw::GameCore( pFramework )
{
    wglSwapInterval( m_VSyncEnabled ? 1 : 0 );
}

Game::~Game()
{
    delete m_pShader;
    delete m_pMeshHuman;
    delete m_pMeshEnemy;
    delete m_pMeshTest;

    for( fw::GameObject* pObject : m_Objects )
    {
        delete pObject;
    }

    delete m_pPlayerController;

    delete m_pEventManager;
    delete m_pImGuiManager;
}

void Game::Init()
{
    m_pImGuiManager = new fw::ImGuiManager( m_pFramework );
    m_pImGuiManager->Init();

    m_pEventManager = new fw::EventManager();

    // Load some shaders.
    m_pShader = new fw::ShaderProgram( "Data/Basic.vert", "Data/Basic.frag" );

    // Create some meshes.
    m_pMeshHuman = new fw::Mesh( meshPrimType_Human, meshNumVerts_Human, meshAttribs_Human );
    m_pMeshEnemy = new fw::Mesh( meshPrimType_Enemy, meshNumVerts_Enemy, meshAttribs_Enemy );

    m_pMeshTest = new fw::Mesh();

    int numPoints = 3;
    {
        //float arr[numPoints*2] = { 0 }; //{ 0,0,   1,0,   2,0 };
        //float* arr = new float[numPoints*2];
        std::vector<float> arr;

        for( int i=0; i<numPoints*2; i++ )
            arr.push_back( 0 );

        for( int i=0; i<numPoints; i++ )
        {
            arr[i*2] = (float)i;
        }
        
        m_pMeshTest->CreateShape( GL_POINTS, numPoints, &arr[0] );
    }

    m_pPlayerController = new PlayerController();

    // Create some GameObjects.
    m_Objects.push_back( new Player( this, m_pPlayerController, "Player", vec2( 6, 5 ), m_pMeshHuman, m_pShader, vec4::Green() ) );
    m_Objects.push_back( new fw::GameObject( this, "Enemy 1", vec2( 0, 0 ),   m_pMeshEnemy, m_pShader, vec4::Red()   ) );
    m_Objects.push_back( new fw::GameObject( this, "Enemy 2", vec2( 10, 10 ), m_pMeshEnemy, m_pShader, vec4::Red()   ) );
    m_Objects.push_back( new fw::GameObject( this, "Enemy 3", vec2( 5, 5 ),   m_pMeshEnemy, m_pShader, vec4::Red()   ) );
    m_Objects.push_back( new fw::GameObject( this, "Enemy 4", vec2( 1, 1 ),   m_pMeshEnemy, m_pShader, vec4::Red()   ) );
    m_Objects.push_back( new fw::GameObject( this, "Enemy 5", vec2( 1, 9 ),   m_pMeshEnemy, m_pShader, vec4::Red()   ) );
    m_Objects.push_back( new fw::GameObject( this, "Test",    vec2( 3, 6 ),   m_pMeshTest,  m_pShader, vec4::Blue()  ) );
}

void Game::OnEvent(fw::Event* pEvent)
{
    m_pPlayerController->OnEvent( pEvent );

    if( pEvent->GetType() == RemoveFromGameEvent::GetStaticEventType() )
    {
        RemoveFromGameEvent* pRemoveFromGameEvent = static_cast<RemoveFromGameEvent*>( pEvent );
        fw::GameObject* pObject = pRemoveFromGameEvent->GetGameObject();

        auto it = std::find( m_Objects.begin(), m_Objects.end(), pObject );
        m_Objects.erase( it );

        delete pObject;
    }
}

void Game::Update(float deltaTime)
{
    // Process our events.
    m_pEventManager->DispatchAllEvents( this );

    m_pImGuiManager->StartFrame( deltaTime );
    ImGui::ShowDemoWindow();

    // Display framerate.
    ImGui::Text( "%0.2f", 1/deltaTime );

    for( auto it = m_Objects.begin(); it != m_Objects.end(); it++ )
    {
        fw::GameObject* pObject = *it;
        pObject->Update( deltaTime );
    }

    // Debug imgui stuff.
    {
        if( ImGui::Checkbox( "VSync", &m_VSyncEnabled ) )
        {
            wglSwapInterval( m_VSyncEnabled ? 1 : 0 );
        }
    }
}

void Game::Draw()
{
    glClearColor( 0, 0, 0.2f, 0 );
    glClear( GL_COLOR_BUFFER_BIT );

    glPointSize( 10 );
    
    for( auto it = m_Objects.begin(); it != m_Objects.end(); it++ )
    {
        fw::GameObject* pObject = *it;
        pObject->Draw();
    }

    m_pImGuiManager->EndFrame();
}
