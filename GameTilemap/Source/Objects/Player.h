#pragma once

class PlayerController;

class Player : public fw::GameObject
{
public:
    Player(fw::GameCore* pGameCore, PlayerController* pPlayerController, std::string name, vec2 pos, fw::Mesh* pMesh, fw::ShaderProgram* pShader, fw::Texture* pTexture, vec4 color);
    virtual ~Player();

    virtual void Update(float deltaTime) override;
    float m_timer = TIMER;
    const float TIMER = 0.5;
protected:
    PlayerController* m_pPlayerController = nullptr;
};
