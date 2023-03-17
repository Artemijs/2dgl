#include "Renderer.h"
#include <iostream>
#include "SDL_mixer.h"
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
	_all_shaders->push_back(new Shader("Shaders/default.vert", "Shaders/default.frag"));
	_all_shaders->push_back(new Shader("Shaders/animated_sprite.vert", "Shaders/animated_sprite.frag"));
	_all_shaders->push_back(new Shader("Shaders/outlineText.vert", "Shaders/outlineText.frag"));

	_all_textures = new std::vector<std::pair<const char*, Texture*>>();
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
	delete _all_graphics;
	Mix_CloseAudio();
	glfwDestroyWindow(_window);
	glfwTerminate();

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
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

void Renderer::Draw() {
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	glClearDepth(1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (int i = 0; i < _all_graphics->size(); ++i) {
		_all_graphics->at(i)->Draw();
	}

	glfwSwapBuffers(_window);
	glfwPollEvents();
}

VAO* Renderer::GetVAO() {
	return _vao;
}
GLFWwindow* Renderer::GetWindow() { return _window; }
Vec2 Renderer::GetWindowSize() { return _windowSize; }
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