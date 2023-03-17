#ifndef RENDERER_H
#define RENDERER_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../BackEnd/EBO.h"
#include "../BackEnd/VBO.h"
#include "../BackEnd/VAO.h"
#include "../BackEnd/FBO.h"
#include <stb/stb_image.h>
#include "../Math/Matrix4x4.h"
#include <vector>

#include "Graphic.h"
#include "ShaderClass.h"
#include "Texture.h"
#include <utility>
#include "../BackEnd/FinalRect.h"
class Renderer {

private:
	GLFWwindow* _window;
	Vec2 _windowSize;
	VAO* _vao;
	VBO* _vbo;
	EBO* _ebo;
	FBO* _fbo;
	GLfloat _vertices[32] = {
		//verices					colors				//uvs
		-0.5f,  -0.5f,  -1.0f,		1.0f, 0.0f, 0.0f,	0.0f, 0.0f, //lower left

		-0.5f,   0.5f,	-1.0f,		0.0f, 1.0f, 0.0f,	0.0f, 1.0f,//upper left 

		 0.5f,	 0.5f,	-1.0f,		0.0f, 0.0f, 1.0f,	1.0f, 1.0f, //upper right

		 0.5f,	-0.5f,	-1.0f,		1.0f, 1.0f, 1.0f,	1.0f, 0.0f //lower right
	};
	GLuint _indices[6] = {
		0, 2, 1, //upper triangle,
		0, 3, 2 //lower triangle
	};

	
	Matrix4x4 _projection;
	std::vector<Shader*>* _all_shaders;
	FinalRect* _fRect;
	void CreateWindow();
	void CreateGeometry();
	std::vector<Graphic*>* _all_graphics;
	std::vector<std::pair<const char*, Texture*>>* _all_textures;
	Renderer();
	static Renderer* _instance;

public :
	~Renderer();
	static Renderer* instance();
	Vec2 GetWindowSize();
	GLFWwindow* GetWindow();
	void Draw();
	VAO* GetVAO();
	void AddGraphic(Graphic* g) {
		_all_graphics->push_back(g);
	}
	void SetShaderVariables(Shader* s);
	Shader* GetShader(int id);
	Texture* GetTexture(int id);
	int LoadTexture(const char* path);
};


#endif // !RENDERER_H




