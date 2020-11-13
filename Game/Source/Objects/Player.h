#pragma once
#include "Collision/Collision.h"

class PlayerController;

class Player : public fw::GameObject
{
public:
    Player(fw::GameCore* pGameCore, PlayerController* pPlayerController, std::string name, vec2 pos, fw::Mesh* pMesh, fw::ShaderProgram* pShader, vec4 color);
    virtual ~Player();

    virtual void Update(float deltaTime) override;
    float GetCurrentSpeed();
    bool GetIsDashing()
    {
        return IsDashing;
    }
    enum PlayerState
    {
        CanDash,
        Dashing,
        Cooldown,
    };
    enum TimerState
    {
        HasToDo,
        Done,
    };

    void SetTimer(float m_time)
    {
        m_timer = m_time;
    }

protected:
    PlayerController* m_pPlayerController = nullptr;
    Collision collision;
    float m_speed;
    float m_timer = 0;
    bool IsDashing = false;
    PlayerState playerstate;
    TimerState timerstate;
};
