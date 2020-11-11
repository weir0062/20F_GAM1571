#include "GamePCH.h"

#include "Objects/Player.h"
#include "Objects/PlayerController.h"
#include "Game.h"

Player::Player(fw::GameCore* pGameCore, PlayerController* pPlayerController, std::string name, vec2 pos, fw::Mesh* pMesh, fw::ShaderProgram* pShader, vec4 color)
    : fw::GameObject( pGameCore, name, pos, pMesh, pShader, color )
    , m_pPlayerController( pPlayerController )
{
}

Player::~Player()
{
}

void Player::Update(float deltaTime)
{
    float speed = 1.0f;
    m_timer -= deltaTime;
    vec2 dir;
    Game* littlegame = static_cast<Game*>(m_pGameCore);
    if (littlegame->GetGamestate() == littlegame->Playing)
    {
        if (m_pPlayerController->IsHeld(PlayerController::Mask::Up))
        {
            dir.y += 1;
        }
        if (m_pPlayerController->IsHeld(PlayerController::Mask::Down))
        {
            dir.y += -1;
        }
        if (m_pPlayerController->IsHeld(PlayerController::Mask::Left))
        {
            dir.x += -1;
        }
        if (m_pPlayerController->IsHeld(PlayerController::Mask::Right))
        {
            dir.x += 1;
        }
        if (m_pPlayerController->IsHeld(PlayerController::Mask::Faster))
        {
            if ( CanDash == true )
            {
                dir.x *= 3;
                dir.y *= 3;
                m_speed = speed *= 3;
                IsDashing = true;
               
                
            }
        }
        else
        {
            m_speed = speed;
        }
        
        
        if (IsDashing == true)
        {
            if (Doonce == true)
            {
                m_timer = 0.2;
                Doonce = false;
            }
            if (m_timer <= 0.0001)
            {
                CanDash = false;
                IsDashing = false;
               
                
           }
        }
        if (IsDashing == false && CanDash == false)
        {
            m_timer = 5.0f;
            if (m_timer <= 0.00001)
            {
                CanDash = true;
            }
        }
       
            if (m_timer <= 0)
            {
                m_timer = 0;
            }
        
        ImGui::Text("%0.2f", m_timer);
        
    }
    if (littlegame->GetGamestate() == littlegame->Lost || littlegame->GetGamestate() == littlegame->Won)
    {
        ImGui::Text("Press R to restart");
        if (m_pPlayerController->IsHeld(PlayerController::Mask::Restart))
        {
            littlegame->Reset();

        }
    }
    
    //dir.Normalize();
  

    m_Position += dir * speed * deltaTime;

    // Deal with collision with the environment.
    {
        // Query Game for environment limits.
        //static_cast<Game*>( m_pGameCore )->

        // Apply those limits.
        if( m_Position.x > 9 )
        {
            m_Position.x = 9;
        }
        if (m_Position.x < 1)
        {
            m_Position.x = 1;
        }
        if (m_Position.y > 9)
        {
            m_Position.y = 9;
        }
        if (m_Position.y < 1)
        {
            m_Position.y = 1;
        }
    }

}

float Player::GetCurrentSpeed()
{
    return m_speed;
}
