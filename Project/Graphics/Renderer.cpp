#include "Renderer.h"
#include <iostream>
#include "SDL_mixer.h"
#include "../UI/RenderNode.h"
Renderer* Renderer::_instance = 0x0;
Renderer* Renderer::instance() {
	if (_instance == 0x0) {
		_instance = new Renderer();
	}
	return _instance;
}


Renderer::Renderer() {
	_windowSize = Vec2(800, 800);
	CreateWindow();
	CreateGeometry();
	_projection = Matrix4x4::Ortho(0.0f, _windowSize.x, 0.0f, _windowSize.y, 0.1f, 1000.0f);
	_all_graphics = new std::vector<Graphic*>();
	_all_shaders = new std::vector<Shader*>();
	_all_shaders->push_back(new Shader("Assets/Shaders/default.vert", "Assets/Shaders/default.frag"));
	_all_shaders->push_back(new Shader("Assets/Shaders/animated_sprite.vert", "Assets/Shaders/animated_sprite.frag"));
	_all_shaders->push_back(new Shader("Assets/Shaders/outlineText.vert", "Assets/Shaders/outlineText.frag"));
	_all_shaders->push_back(new Shader("Assets/Shaders/final_rect.vert", "Assets/Shaders/final_rect.frag"));
	//_all_shaders->push_back();

	_all_textures = new std::vector<std::pair<const char*, Texture*>>();

	_fbo = new FBO(_windowSize.x, _windowSize.y);
	
	_fRect = new FinalRect();

}
Renderer::~Renderer() {

	for (int i = 0; i < _all_shaders->size(); ++i) {
		_all_shaders->at(i)->Delete();
		delete _all_shaders->at(i);
	}
	delete _all_shaders;

	for (int i = 0; i < _all_textures->size(); ++i) {
		_all_textures->at(i).second->Delete();
		delete _all_textures->at(i).second;
	}
	delete _all_textures;

	_vao->Delete();
	_vbo->Delete();
	_ebo->Delete();
	delete _vao; 
	delete _vbo;
	delete _ebo;
	delete _fbo;
	delete _all_graphics;
	Mix_CloseAudio();
	glfwDestroyWindow(_window);
	glfwTerminate();
	delete _fRect;
	//glDeleteFramebuffers(1, &_fbo);
	//glDeleteTextures(1, &_fboTex);
	//glDeleteRenderbuffers(1, _
}

void Renderer::CreateGeometry() {
	_vao = new VAO();
	_vao->Bind();

	_vbo = new VBO(_vertices, sizeof(_vertices));
	_ebo = new EBO(_indices, sizeof(_indices));

	_vao->LinkAttrib(_vbo, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	_vao->LinkAttrib(_vbo, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	_vao->LinkAttrib(_vbo, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	_vao->Unbind();
	_vbo->Unbind();
	_ebo->Unbind();
}
void Renderer::CreateWindow() {
	glfwInit();
	glfwInitHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwInitHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwInitHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	_window = glfwCreateWindow(_windowSize.x, _windowSize.y, "SOON_TM", NULL, NULL);
	if (_window == NULL) {

		std::cout << "failed to create window \n";
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(_window);
	gladLoadGL();
	glViewport(0, 0, _windowSize.x, _windowSize.y);
	glEnable(GL_DEPTH_TEST);


}

void Renderer::Draw() {

	/*glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	glClearDepth(1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	for (int i = 0; i < _all_graphics->size(); ++i) {
		_all_graphics->at(i)->Draw();
	}

	glfwSwapBuffers(_window);
	glfwPollEvents();
	*/

	glBindFramebuffer(GL_FRAMEBUFFER, _fbo->_fbo);
	
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);


	for (int i = 0; i < _all_graphics->size(); ++i) {
		_all_graphics->at(i)->TryDraw();
	
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	
	//DRAW THE FINAL SCREEN RECTANGLE
	
	
	_fRect->Bind();
	glDisable(GL_DEPTH_TEST);
	glBindTexture(GL_TEXTURE_2D, _fbo->_fboTex);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	_fRect->Unbind();
	glBindTexture(GL_TEXTURE_2D, 0);
	
	
	glfwSwapBuffers(_window);
	glfwPollEvents();//<------------- THIS SHOULD BE IN MAIN ?
}

VAO* Renderer::GetVAO() {
	return _vao;
}
GLFWwindow* Renderer::GetWindow() { return _window; }
Vec2 Renderer::GetWindowSize() { return _windowSize; }
Vec3 Renderer::WindowSizeVec3() { return Vec3(_windowSize.x, _windowSize.y, 1.0f); }
/// <summary>
/// set projection and camera view matrix
/// </summary>
/// <param name="s"></param>
void Renderer::SetShaderVariables(Shader* s) {
	glUniformMatrix4fv(glGetUniformLocation(s->ID, "proj"), 1, GL_TRUE, &_projection.buff[0]);

}
Shader* Renderer::GetShader(int id) {
	return _all_shaders->at(id);
}
Texture* Renderer::GetTexture(int id) {
	return _all_textures->at(id).second;
}
int Renderer::LoadTexture(const char* path) {
	//check if exissts
	bool found = false;
	for (int i = 0; i < _all_textures->size(); ++i) {
		const char* p = _all_textures->at(i).first;
		for (int j = 0; p[j] == path[j]; j++) {
			//if strings are identical
			 if(p[j] == '\0' && path[j] == '\0'){
				//dont need to add it because it already exists
				found = true;
				return i;
				break;
			}
		}
	}
	if(!found)
	//add new if not exists
	_all_textures->push_back(
		std::pair<const char*, Texture*>{path, new Texture(path, GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE)});
	return _all_textures->size() - 1;
}

void Renderer::DrawNodes(BaseObject* node, BaseObject* last) {
	/*
	drawNode(node, last){

		if(node == renderNode){
			bind node;
		}

		if (children =! null)
			for(int i = 0; i < children.size(); ++i){
				drawNode(children[i], NODE);
			}

		if(node == renderNode)
			BIND LAST
		if(parent == null)
			//DRAW ROOT TO FINAL RECT
		node->draw();
	}
	*/
	bool renderNode = (node->GetNodeType() == 2);
	RenderNode* rn = NULL;
	if (renderNode) {
		//bind node fbo
		rn = node->GetComponent<RenderNode>();
		glBindFramebuffer(GL_FRAMEBUFFER, rn->GetFBO()._fbo);
		
	}
	const std::vector<BaseObject*>* children = node->GetAllChildren();
	if (children != NULL)
		for (int i = 0; i < children->size(); ++i) {
		
		}
	if (renderNode) {
		//bind last fbo
		glBindFramebuffer(GL_FRAMEBUFFER, last->GetComponent<RenderNode>()->GetFBO()._fbo);
	}
	if(node->GetParent() == NULL){
		//DRAW ROOT TO FINLal RECT
	}
	if (node->GetNodeType() == 1) {
		node->GetComponent<Graphic>()->TryDraw();
	}
	else if (renderNode) {
		//bind vao
		_vao->Bind();
		//activate shader
		//set shader vars
		//bind texture from FBO
		// 
		//draw triangles
		// 
		//unbind vao
		//deactivate shader
		//unbind texture
	}

}