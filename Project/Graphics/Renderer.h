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
#include "../Game/BaseNode.h"
#include "Camera.h"
#include "../Game/FBOComponent.h"
#include "Materials/MaterialUiSprite.h"
#include "../Game/RenderNode.h"

class Renderer {

private:
	GLFWwindow* _window;
	Vec2 _windowSize;

	FBO* _fbo;
	FinalRect* _fRect;
	MaterialUiNoTex* _fboMat;


	VAO* _vao;
	VBO* _vbo;
	EBO* _ebo;
	std::vector<Vertex> _vertices = 
	{
		//positions							//normals			//uv
		Vertex{Vec3(-0.5f,  -0.5f,  0), Vec3(0, 0, 0), Vec2(0.0f, 0.0f)},
		Vertex{Vec3(-0.5f,  0.5f,  0),  Vec3(0, 0, 0), Vec2(0.0f, 1.0f)}, 
		Vertex{Vec3(0.5f,  0.5f,  0),   Vec3(0, 0, 0), Vec2(1.0f, 1.0f)},  
		Vertex{Vec3(0.5f,  -0.5f,  0),  Vec3(0, 0, 0), Vec2(1.0f, 0.0f)}  
	};
	std::vector<GLuint> _indices= {
		0, 2, 1, //upper triangle,
		0, 3, 2 //lower triangle
	};

	
	Matrix4x4 _projection;
	Matrix4x4 _uiProjection;

	std::vector<Shader*>* _all_shaders;
	std::vector<Graphic*>* _all_graphics;
	std::vector<std::pair<const char*, Texture*>>* _all_textures;
	
	Camera* _camera;
	
	static Renderer* _instance;
	
	Renderer();
	void CreateWindow();
	void CreateGeometry();

	void TurnRenderNodeOn(RenderNode*& rn, BaseNode* node, const FBOComponent*& fbo);
	void DrawRenderNode(const RenderNode* parent, const BaseNode* node, const FBOComponent* fbo);
	void DrawFinalRect(const BaseNode* node, const FBOComponent* fbo);

public:
	~Renderer();
	static Renderer* instance();
	Vec2 GetWindowSize();
	const Vec3 WindowSizeVec3();
	GLFWwindow* GetWindow();
	void Draw(const BaseNode* n);

	void DrawNodes(BaseNode* node, RenderNode* lastFbo);
	
	VAO* GetVAO();
	void AddGraphic(Graphic* g) {						
		_all_graphics->push_back(g);					
	}													
	void SetShaderVariables(const unsigned int shaderID);
	/*
	"Assets/Shaders/defaultNoTex.vert", "Assets/Shaders/defaultNoTex.frag"));//0
	"Assets/Shaders/ui_sprite.vert", "Assets/Shaders/ui_sprite.frag"));
	"Assets/Shaders/ui_animated_sprite.vert", "Assets/Shaders/ui_animated_sprite.frag"));
	"Assets/Shaders/ui_outlineText.vert", "Assets/Shaders/ui_outlineText.frag"));
	"Assets/Shaders/final_rect.vert", "Assets/Shaders/final_rect.frag"));//4
	"Assets/Shaders/diffuse.vert", "Assets/Shaders/diffuse.frag"));
	"Assets/Shaders/Experimental/eperiment_0.vert", "Assets/Shaders/Experimental/eperiment_0.frag"));
	"Assets/Shaders/sprite.vert", "Assets/Shaders/sprite.frag"));
*/
	Shader* GetShader(int id);							
	Texture* GetTexture(int id);						
	/// <summary>
	/// loads a textures and stores it, if it exists returns an existing one
	/// </summary>
	/// <param name="type">textures name in the shader it is used in</param>
	/// <param name="path"></param>
	/// <returns></returns>
	const Texture* LoadTexture(const char* type, const char* path);		
	const Texture* LoadTexture(const char* type, const char* path, unsigned int gl_slot);
	Matrix4x4* GetProjection();
	Matrix4x4* GetUIProjection();
	Camera* GetCamera();
};


#endif // !RENDERER_H




