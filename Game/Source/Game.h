#pragma once


class Game : public fw::GameCore
{
public:
    Game(fw::FWCore* pFrawework);
    virtual ~Game();

    void Init();
    virtual void Update(float delta) override;
    virtual void Draw() override;

protected:
    fw::ShaderProgram* m_pShader = nullptr;
    fw::Mesh* m_pMeshHuman = nullptr;
    fw::Mesh* m_pMeshAnimal = nullptr;
    fw::ImGuiManager* m_GUIMANAGER;
    std::vector<fw::GameObject*> m_Objects;
};
