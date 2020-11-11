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

protected:
    PlayerController* m_pPlayerController = nullptr;
    Collision collision;
    float m_speed;
    float m_timer = 0;
    bool CanDash = true;
    bool IsDashing = false;
    bool Doonce = true;
};
