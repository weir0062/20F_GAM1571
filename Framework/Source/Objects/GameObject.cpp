#include "FrameworkPCH.h"

#include "GameObject.h"
#include "Mesh.h"

namespace fw {

GameObject::GameObject(float x, float y, Mesh* pMesh, ShaderProgram* pShader)
{
    m_PosX = x;
    m_PosY = y;

    m_pMesh = pMesh;
    m_pShader = pShader;
}

GameObject::~GameObject()
{
}

void GameObject::Update()
{
}

void GameObject::Draw()
{
    m_pMesh->Draw( m_PosX, m_PosY, m_pShader );
}

} // namespace fw
