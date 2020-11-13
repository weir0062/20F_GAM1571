#include "GamePCH.h"

#include "Objects/Player.h"
#include "Objects/PlayerController.h"
#include "Game.h"

Player::Player(fw::GameCore* pGameCore, PlayerController* pPlayerController, std::string name, vec2 pos, fw::Mesh* pMesh, fw::ShaderProgram* pShader, vec4 color)
    : fw::GameObject( pGameCore, name, pos, pMesh, pShader, color )
    , m_pPlayerController( pPlayerController )
{
    playerstate = CanDash;
    timerstate = HasToDo;
}

Player::~Player()
{
}

void Player::Update(float deltaTime)
{
    float speed = 1.0f;
    m_timer -= deltaTime;
    if (m_timer <= 0.0001)
    {
        m_timer = 0;
    }
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
            if (playerstate != Cooldown)
            {
                dir.x *= 3;
                dir.y *= 3;
                m_speed = speed *= 3;
                playerstate = Dashing;
            }
               
        }
        else
        {
            m_speed = speed;
        }
        if (playerstate == Dashing)
        {
            if (timerstate == HasToDo)
            {
                m_timer = 0.5;
                timerstate = Done;
            }


            if (m_timer <= 0.0003)
            {
                playerstate = Cooldown;
                timerstate = HasToDo;
            }
        }

        if (playerstate == Cooldown)
        {
            if (timerstate == HasToDo)
            {
                m_timer = 3;
                timerstate = Done;
            }
            if (m_timer <= 0.0003)
            {
                playerstate = CanDash;
                timerstate = HasToDo;

            }
        }
        if (playerstate == CanDash)
        {
            m_timer = 0;
        }
      
        ImGui::Text("Cooldown: %0.1f", m_timer);
        
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
