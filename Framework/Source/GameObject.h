#pragma once



namespace fw {


	class Mesh;
	class ShaderProgram;
	
	class GameObject
	{
	public:

		GameObject();
		virtual ~GameObject();
		void Update();
		void Draw();
		float m_x;
		float m_y;
		fw::Mesh* m_mesh;
		fw::ShaderProgram* pShader;



	};
}
