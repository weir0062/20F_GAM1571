#pragma once
namespace fw {

    class ShaderProgram;
	 
class Mesh
{
public:
    Mesh(int what);
    virtual ~Mesh();

    void Draw(float poisition_x, float position_y, fw::ShaderProgram* pShader );
    void Lines();
    void Triangles();

protected:
    GLuint m_VBO = 0;

    int m_NumVertices = 0;
    int m_PrimitiveType = GL_POINTS;
};

    
} // namespace fw
