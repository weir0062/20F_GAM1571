#pragma once

#include "Math/Vector.h"

namespace fw {

class Mesh;
class ShaderProgram;
class GameCore;

class GameObject
{
public:
    GameObject(GameCore* pGameCore, std::string name, vec2 pos, Mesh* pMesh, ShaderProgram* pShader, vec4 color);
    virtual ~GameObject();

    virtual void Update(float deltaTime);
    virtual void Draw();

    std::string GetName() { return m_Name; }
    void SetPosition(vec2 Position)
    {
        m_Position = Position;
    }
    vec2 GetPosition() { return m_Position; }
    void Deleteme(bool m_delete)
    {
        deleteme = m_delete;
    }
    bool GetDeleteme()
    {
        return deleteme;
    }

protected:
    GameCore* m_pGameCore = nullptr;

    std::string m_Name;

    vec2 m_Position;

    Mesh* m_pMesh = nullptr;
    ShaderProgram* m_pShader = nullptr;
    vec4 m_Color = vec4(1,1,1,1);
    bool deleteme;
   
};

} // namespace fw
