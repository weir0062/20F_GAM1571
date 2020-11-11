#include "FrameworkPCH.h"

#include "Mesh.h"
#include "Utility/ShaderProgram.h"
#include "Utility/Helpers.h"

namespace fw {

Mesh::Mesh()
{
}

Mesh::Mesh(int primitiveType, int numVertices, const float* pVertices)
{
    CreateShape( primitiveType, numVertices, pVertices );
}

Mesh::~Mesh()
{
    glDeleteBuffers( 1, &m_VBO );
}

void Mesh::CreateShape(int primitiveType, int numVertices, const float* pVertices)
{
    // Delete the old buffer if we had one.
    glDeleteBuffers( 1, &m_VBO );

    // Generate a buffer for our vertex attributes.
    glGenBuffers( 1, &m_VBO ); // m_VBO is a GLuint.

    // Set this VBO to be the currently active one.
    glBindBuffer( GL_ARRAY_BUFFER, m_VBO );

    m_NumVertices = numVertices;
    m_PrimitiveType = primitiveType;

    // Copy our attribute data into the VBO.
    int numAttributeComponents = m_NumVertices*2; // x & y for each vertex.
    glBufferData( GL_ARRAY_BUFFER, sizeof(float)*numAttributeComponents, pVertices, GL_STATIC_DRAW );
}

void Mesh::SetUniform1f(ShaderProgram* pShader, char* name, float value)
{
    int loc = glGetUniformLocation( pShader->GetProgram(), name );
    glUniform1f( loc, value );
}

void Mesh::SetUniform2f(ShaderProgram* pShader, char* name, vec2 value)
{
    int loc = glGetUniformLocation( pShader->GetProgram(), name );
    glUniform2f( loc, value.x, value.y );
}

void Mesh::SetUniform4f(ShaderProgram* pShader, char* name, vec4 value)
{
    int loc = glGetUniformLocation( pShader->GetProgram(), name );
    glUniform4f( loc, value.x, value.y, value.z, value.w );
}

void Mesh::Draw(vec2 pos, ShaderProgram* pShader, vec4 color)
{
    glUseProgram( pShader->GetProgram() );

    // Set this VBO to be the currently active one.
    glBindBuffer( GL_ARRAY_BUFFER, m_VBO );

    // Get the attribute variable�s location from the shader.
    GLint loc = 0; //glGetAttribLocation( m_pShader->m_Program, "a_Position" );
    glEnableVertexAttribArray( loc );

    // Describe the attributes in the VBO to OpenGL.
    glVertexAttribPointer( loc, 2, GL_FLOAT, GL_FALSE, 8, (void*)0 );

    // Setup our uniforms.
    {
        SetUniform1f( pShader, "u_Time", (float)GetSystemTimeSinceGameStart() );
        SetUniform2f( pShader, "u_ObjectPos", pos );
        SetUniform4f( pShader, "u_Color", color );
    }

    // Draw the primitive.
    glDrawArrays( m_PrimitiveType, 0, m_NumVertices );
}

} // namespace fw
