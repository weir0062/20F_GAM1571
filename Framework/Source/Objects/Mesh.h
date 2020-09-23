#pragma once

namespace fw {

class ShaderProgram;

class Mesh
{
public:
    Mesh();
    Mesh(int primitiveType, int numVertices, float* pVertices);
    virtual ~Mesh();

    void CreateShape(int primitiveType, int numVertices, float* pVertices);

    void Draw(float x, float y, ShaderProgram* pShader);

protected:
    GLuint m_VBO = 0;

    int m_NumVertices = 0;
    int m_PrimitiveType = GL_POINTS;
};

} // namespace fw
