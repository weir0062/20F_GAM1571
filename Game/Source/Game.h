#pragma once
class GameObject;
class Game : public fw::GameCore
{
public:
    Game();
    virtual ~Game();

    void Init();
    virtual void Update() override;
    virtual void Draw() override;

protected:
    fw::ShaderProgram* m_pShader = nullptr;
    fw::Mesh* m_pMesh = nullptr;
    fw::Mesh* m_pMesh2 = nullptr;
    std::vector<GameObject*> m_pMeshes[2];
};
