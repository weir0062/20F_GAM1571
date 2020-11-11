#include "GamePCH.h"

#include "Game.h"
#include "Objects/Player.h"
#include "Objects/PlayerController.h"
#include "Objects/Shapes.h"
#include "Events/GameEvents.h"
#include "Collision/Collision.h"

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
    // OpenGL Settings.
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    gamestate = Playing;
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
    m_pPlayer = new Player(this, m_pPlayerController, "Player", vec2(6, 5), m_pMeshHuman, m_pShader, vec4(0.0f, 1.0f, 0.0f, 0.5f));

    Reset();
    m_Objects.push_back(m_pPlayer);
}

void Game::StartFrame(float deltaTime)
{
    m_pImGuiManager->StartFrame( deltaTime );

    m_pPlayerController->StartFrame();

    // Process our events.
    m_pEventManager->DispatchAllEvents( this );
}

void Game::OnEvent(fw::Event* pEvent)
{
    m_pPlayerController->OnEvent( pEvent );

    if (pEvent->GetType() == "CollisionEvent")
    {
        if (m_pPlayer->GetCurrentSpeed() == 1)
        {
            gamestate = Lost;

        }
        if (m_pPlayer->GetIsDashing() == true)
        {
            if (m_pPlayer->GetCurrentSpeed() == 3)
            {


                fw::GameObject* object = static_cast<fw::CollisionEvent*>(pEvent)->GetsecondObject();
                object->Deleteme(true);

            }
        }
        
    }

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
    //ImGui::ShowDemoWindow();

    // Display framerate.
    ImGui::Text( "%0.2f", 1/deltaTime );

    for( auto it = m_Objects.begin(); it != m_Objects.end(); it++ )
    {
        fw::GameObject* pObject = *it;
        pObject->Update( deltaTime );
    }

    // Check for collisions between objects.
    // Single For loop checking the player against everything else
    //   or
    // Nested For loop checking everything against everything else
    
    
  
    for (int i = 0; i < m_Objects.size(); i++)
    {
        if(m_pPlayer == m_Objects[i])
        { 
            continue;
        }

        float ObjectX = m_Objects[i]->GetPosition().x;
        float ObjectY = m_Objects[i]->GetPosition().y;
        float PlayerX = m_pPlayer->GetPosition().x;
        float PlayerY = m_pPlayer->GetPosition().y;
        if (ObjectX >= PlayerX - 0.2 && ObjectX <= PlayerX && ObjectY <= PlayerY + 0.2 && ObjectY >= PlayerY-0.2)
        {
           // ImGui::Text(" Left Collision Detected");
            fw::CollisionEvent* Collision;
            Collision = new fw::CollisionEvent(m_pPlayer, m_Objects[i]);
            GetEventManager()->AddEvent(Collision);
        }
        if (ObjectX <= PlayerX + 0.33 && ObjectX >= PlayerX && ObjectY <= PlayerY + 0.2 && ObjectY >= PlayerY - 0.2)
        {
          //  ImGui::Text(" Right Collision Detected");
            fw::CollisionEvent* Collision;
            Collision = new fw::CollisionEvent(m_pPlayer, m_Objects[i]);
            GetEventManager()->AddEvent(Collision);
        }
        if (ObjectY >= PlayerY - 0.33 && ObjectY <= PlayerY && ObjectX >= PlayerX - 0.2 && ObjectX <= PlayerX +0.2)
        {
        //   ImGui::Text(" Bottom Collision Detected");
            fw::CollisionEvent* Collision;
            Collision = new fw::CollisionEvent(m_pPlayer, m_Objects[i]);
            GetEventManager()->AddEvent(Collision);
        }
        if (ObjectY <= PlayerY + 0.33 && ObjectY >= PlayerY && ObjectX >= PlayerX - 0.2 && ObjectX <= PlayerX + 0.2)
        {
          //  ImGui::Text(" Top Collision Detected");
            fw::CollisionEvent* Collision;
            Collision = new fw::CollisionEvent(m_pPlayer, m_Objects[i]);
            GetEventManager()->AddEvent(Collision);
        }

        if (m_Objects[i]->GetDeleteme() == true)
        {
            RemoveFromGameEvent* DeleteEvent;
            DeleteEvent = new RemoveFromGameEvent(m_Objects[i]);
            GetEventManager()->AddEvent(DeleteEvent);
        }

    }
    
        if (m_Objects.size() == 1)
        {
            gamestate = Won;
            ImGui::Text("WON!!!");
        }
        
        if (gamestate == Lost)
        {
            ImGui::Text("Lost!!!");
            for (int i = 0; i < m_Objects.size(); i++)
            {
                if (m_Objects[i] == m_pPlayer)
                {
                    continue;
                }
                RemoveFromGameEvent* DeleteEvent;
                DeleteEvent = new RemoveFromGameEvent(m_Objects[i]);
                GetEventManager()->AddEvent(DeleteEvent);

            }
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

void Game::Reset()
{


    gamestate = Playing;
   
    m_Objects.push_back(new fw::GameObject(this, "Enemy 1", vec2(3, 3), m_pMeshEnemy, m_pShader, vec4::Red()));
    m_Objects.push_back(new fw::GameObject(this, "Enemy 2", vec2(7, 7), m_pMeshEnemy, m_pShader, vec4::Red()));
    m_Objects.push_back(new fw::GameObject(this, "Enemy 3", vec2(5, 5), m_pMeshEnemy, m_pShader, vec4::Red()));
    m_Objects.push_back(new fw::GameObject(this, "Enemy 4", vec2(2, 2), m_pMeshEnemy, m_pShader, vec4::Red()));
    m_Objects.push_back(new fw::GameObject(this, "Enemy 5", vec2(2, 8), m_pMeshEnemy, m_pShader, vec4::Red()));
    m_pPlayer->SetPosition(vec2(6, 5));
}
