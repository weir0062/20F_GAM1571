#include "GamePCH.h"

#include "Objects/Player.h"
#include "Objects/PlayerController.h"
#include "Game.h"

Player::Player(fw::GameCore* pGameCore, PlayerController* pPlayerController, std::string name, vec2 pos, fw::Mesh* pMesh, fw::ShaderProgram* pShader, fw::Texture* pTexture, vec4 color)
    : fw::GameObject( pGameCore, name, pos, pMesh, pShader, pTexture, color )
    , m_pPlayerController( pPlayerController )
{
}

Player::~Player()
{
}

void Player::Update(float deltaTime)
{
    float speed = 2.0f;

    vec2 dir;
    m_timer -= deltaTime;
    if (m_timer <= 0)
    {
        m_timer = TIMER;
    }
    m_UVScale = vec2(64.0 / 1024.0, 64.0 / 512.0);
    m_UVOffset = vec2(780.0 / 1024.0, 318 / 512.0);

    if( m_pPlayerController->IsHeld( PlayerController::Mask::Up ) )
    {
        dir.y += 1;
        if (m_timer < TIMER / 2)
        {
            m_UVScale = vec2(64.0 / 1024.0, 64.0 / 512.0);
            m_UVOffset = vec2(910 / 1024.0, 448 / 512.0);
        }
        else
        {
            m_UVScale = vec2(64.0 / 1024.0, 64.0 / 512.0);
            m_UVOffset = vec2(845 / 1024.0, 383.0 / 512.0);
        }


    }
    if( m_pPlayerController->IsHeld( PlayerController::Mask::Down ) )
    {
        dir.y += -1;
        if (m_timer < TIMER/2)
        {
            m_UVScale = vec2(64.0 / 1024.0, 64.0 / 512.0);
            m_UVOffset = vec2(780.0 / 1024.0, 318 / 512.0);
        }
        else
        {
            m_UVScale = vec2(64.0 / 1024.0, 64.0 / 512.0);
            m_UVOffset = vec2(715.0 / 1024.0, 253.0 / 512.0);
        }
    }
    if( m_pPlayerController->IsHeld( PlayerController::Mask::Left ) )
    {
        dir.x += -1;
        if (m_timer < TIMER / 2)
        {
            m_UVScale = vec2(64.0 / 1024.0, 64.0 / 512.0);
            m_UVOffset = vec2(910 / 1024.0, 318 / 512.0);

        }
        else
        {
            m_UVScale = vec2(64.0 / 1024.0, 64.0 / 512.0);
            m_UVOffset = vec2(780 / 1024.0, 123 / 512.0);
        }
    }
    if( m_pPlayerController->IsHeld( PlayerController::Mask::Right ) )
    {
        dir.x += 1;
        if (m_timer < TIMER / 2)
        {
            m_UVScale = vec2(64.0 / 1024.0, 64.0 / 512.0);
            m_UVOffset = vec2(780 / 1024.0, 188 / 512.0);
        }
        else
        {
            m_UVScale = vec2(64.0 / 1024.0, 64.0 / 512.0);
            m_UVOffset = vec2(715 / 1024.0, 123 / 512.0);
        }
    }

  
    //dir.Normalize();

    m_Position += dir * speed * deltaTime;

    // Deal with collision with the environment.
    {
        // Query Game for environment limits.
        //static_cast<Game*>( m_pGameCore )->

        // Apply those limits.
        if( m_Position.x > 8 )
        {
            m_Position.x = 8;
        }
    }
}
