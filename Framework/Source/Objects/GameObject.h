#pragma once

namespace fw {

class Mesh;
class ShaderProgram;

class GameObject
{
public:
    GameObject(float x, float y, Mesh* pMesh, ShaderProgram* pShader);
    virtual ~GameObject();

    void Update();
    void Draw();

protected:
    float m_PosX = 0;
    float m_PosY = 0;

    Mesh* m_pMesh = nullptr;
    ShaderProgram* m_pShader = nullptr;
};

} // namespace fw
