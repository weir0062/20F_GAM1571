#include "FrameworkPCH.h"

#include "Mesh.h"

namespace fw {

Mesh::Mesh(int what)
{
  if (what == 1)
  {
      Lines();
  }
	if (what == 2)
	{
        Triangles();
	}
}

Mesh::~Mesh()
{
}

void Mesh::Draw(float poisition_x, float position_y, fw::ShaderProgram* pShader)
{
	
    // Set this VBO to be the currently active one.
    glBindBuffer( GL_ARRAY_BUFFER, m_VBO );

    // Get the attribute variable’s location from the shader.
    GLint loc = 0; //glGetAttribLocation( m_pShader->m_Program, "a_Position" );
    glEnableVertexAttribArray( loc );

    // Describe the attributes in the VBO to OpenGL.
    glVertexAttribPointer( loc, 2, GL_FLOAT, GL_FALSE, 8, (void*)0 );

    // Draw the primitive.
    glDrawArrays( m_PrimitiveType, 0, m_NumVertices );
}
void Mesh::Lines()
{
    // Generate a buffer for our vertex attributes.
    glGenBuffers(1, &m_VBO); // m_VBO is a GLuint.

    // Set this VBO to be the currently active one.
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

    // Define our triangle as 3 positions.
    float attribs[] =
    {
        -0.7f, 0.5f,
         0.0f, 0.5f,
         0.0f, 0.5f,
    	 0.2f, 0.7f,
         0.0f, 0.5f,
    	 0.0f, 0.2f,
    	 0.0f, 0.2f,
    	-0.7f, 0.2f,
    	-0.7f, 0.2f,
    	-0.7f, 0.3f,
    	-0.7f, 0.3f,
    	-0.9f, 0.3f,
        -0.9f, 0.3f,
        -0.9f, 0.5f,
    	-0.9f, 0.5f,
    	-0.7f, 0.5f,
    	-0.9f, 0.5f,
    	-0.875f, 0.6f,
    	-0.875f, 0.6f,
    	-0.85f, 0.5f,
        -0.85f, 0.5f,
        -0.825f, 0.6f,
        -0.825f, 0.6f,
        -0.8f, 0.5f,
        -0.7f, 0.2f,
        -0.7f, -0.2f,
        -0.6f, 0.2f,
        -0.6f, -0.2f,
        -0.1f, 0.2f,
        -0.1f, -0.2f,
         0.0f, 0.2f,
         0.0f, -0.2f,
    	
       




    };

    m_NumVertices = 32;
    m_PrimitiveType = GL_LINES;

    // Copy our attribute data into the VBO.
    int numAttributeComponents = m_NumVertices * 2; // x & y for each vertex.
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * numAttributeComponents, attribs, GL_STATIC_DRAW);
}

void Mesh::Triangles()
{
    // Generate a buffer for our vertex attributes.
    glGenBuffers(1, &m_VBO); // m_VBO is a GLuint.

    // Set this VBO to be the currently active one.
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

    // Define our triangle as 3 positions.
    float attribs[] =
    {
       
        
        0.3f, -0.5f,
        0.2f, 0.0f,
    	0.5f, 0.0f,
        0.5f, 0.0f,
    	0.8f, 0.0f,
    	0.7f, -0.5f,
    	0.2f, 0.0f,
    	0.8f, 0.0f,
    	0.5f, 0.5f,
        0.5f, 0.5f,
    	0.5f, 0.3f,
    	0.0f, 0.5f,
        0.5f, 0.5f,
        0.5f, 0.3f,
    	1.0f, 0.5f,
    	0.4f, 0.5f,
    	0.6f, 0.5f,
    	0.4f, 0.8f,
        0.6f, 0.5f,
        0.4f, 0.8f,
    	0.6f, 0.8f,



    };

    m_NumVertices = 21;
    m_PrimitiveType = GL_TRIANGLES;

    // Copy our attribute data into the VBO.
    int numAttributeComponents = m_NumVertices * 2; // x & y for each vertex.
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * numAttributeComponents, attribs, GL_STATIC_DRAW);
}

} // namespace fw
