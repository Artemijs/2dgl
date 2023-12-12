#include "Graphics/Renderer.h"
#include <iostream>
#include "SDL_mixer.h"
//#include "../UI/RenderNode.h"
#include "Graphics/Sprite.h"
#include "Game/Game.h"
#include "Util/Utility.h"





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
	_uiProjection = Matrix4x4::Ortho(0.0f, _windowSize.x, 0.0f, _windowSize.y, 0.1f, 1000.0f);;
	_projection = Matrix4x4::Ortho(0.0f, _windowSize.x, 0.0f, _windowSize.y, 0.1f, 1000.0f);
	_all_graphics = new std::vector<Graphic*>();
	_all_shaders = new std::vector<Shader*>();
	_all_shaders->push_back(new Shader(ASSETS"Shaders/defaultNoTex.vert", ASSETS"Shaders/defaultNoTex.frag"));//0			
	_all_shaders->push_back(new Shader(ASSETS"Shaders/ui_sprite.vert", ASSETS"Shaders/ui_sprite.frag"));
	_all_shaders->push_back(new Shader(ASSETS"Shaders/ui_animated_sprite.vert", ASSETS"Shaders/ui_animated_sprite.frag"));
	_all_shaders->push_back(new Shader(ASSETS"Shaders/ui_outlineText.vert", ASSETS"Shaders/ui_outlineText.frag"));
	_all_shaders->push_back(new Shader(ASSETS"Shaders/final_rect.vert", ASSETS"Shaders/final_rect.frag"));//4
	_all_shaders->push_back(new Shader(ASSETS"Shaders/diffuse.vert", ASSETS"Shaders/diffuse.frag"));
	_all_shaders->push_back(new Shader(ASSETS"Shaders/Experimental/eperiment_0.vert", ASSETS"Shaders/Experimental/eperiment_0.frag"));
	_all_shaders->push_back(new Shader(ASSETS"Shaders/sprite.vert", ASSETS"Shaders/sprite.frag"));
	_all_shaders->push_back(new Shader(ASSETS"Shaders/ui_renderNode.vert", ASSETS"Shaders/ui_renderNode.frag"));//8

	_all_textures = new std::vector<std::pair<const char*, Texture*>>();

	_fbo = new FBO(_windowSize.x, _windowSize.y);

	_fRect = new FinalRect();

	_camera = new Camera(_windowSize.x, _windowSize.y, Vec3(0, 0, 100));

	_fboMat = new MaterialUiNoTex(_all_shaders->at(1));

	_extraDrawCalls = new std::vector<std::function<void()>*>();

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
	delete _camera;
	delete _fboMat;

	for (int i = 0; i < _extraDrawCalls->size(); i++) {
		delete _extraDrawCalls->at(i);
	}
	delete _extraDrawCalls;
}

void Renderer::CreateGeometry() {
	_vao = new VAO();
	_vao->Bind();

	_vbo = new VBO(_vertices);
	_ebo = new EBO(_indices);

	_vao->LinkAttrib(_vbo, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);//positions
	_vao->LinkAttrib(_vbo, 2, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));//normals
	_vao->LinkAttrib(_vbo, 1, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float))); //uvs
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
	// Keeps front faces
	glCullFace(GL_FRONT);
	// Uses counter clock-wise standard
	glFrontFace(GL_CCW);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}


///debug function that draws everything to _fbo with root model matrix
void Renderer::Draw(const BaseNode* n) {

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	FBOComponent* f = Game::_world->GetComponent<FBOComponent>();
	//FBOComponent* f = Game::_world->GetComponent<FBOComponent>();
	glBindFramebuffer(GL_FRAMEBUFFER, f->_fbo);
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	const std::vector<BaseNode*>* children = n->GetAllChildren();

	if (children != NULL) {
		for (int i = 0; i < children->size(); ++i) {
			auto child = children->at(i);
			auto  comps = child->Components();
			for (int i = 0; i < comps->size(); ++i) {
				if (comps->at(i)->second->IsGraphic()) {
					
					dynamic_cast<Graphic*>(comps->at(i)->second)->Draw(child->GetModelMatrix());
				}
			}
		}
	}
	DrawFinalRect(NULL, f);
}

VAO* Renderer::GetVAO() {
	return _vao;
}
GLFWwindow* Renderer::GetWindow() { return _window; }
Vec2 Renderer::GetWindowSize() { return _windowSize; }
const Vec3 Renderer::WindowSizeVec3() { return Vec3(_windowSize.x, _windowSize.y, 0.0f); }
/// <summary>
/// set projection and camera view matrix
/// </summary>
/// <param name="s"></param>
void Renderer::SetShaderVariables(const unsigned int shaderID) {
	glUniformMatrix4fv(glGetUniformLocation(shaderID, "proj"), 1, GL_TRUE, &_projection.buff[0]);

}


Shader* Renderer::GetShader(int id) {
	return _all_shaders->at(id);
}
Texture* Renderer::GetTexture(int id) {
	return _all_textures->at(id).second;
}


const Texture* Renderer::LoadTexture(const char* type, const char* path) {
	//check if exissts
	for (int i = 0; i < _all_textures->size(); ++i) {
		const char* p = _all_textures->at(i).first;

		for (int j = 0; p[j] == path[j]; j++) {
			//if strings are identical
			if (p[j] == '\0' && path[j] == '\0') {
				//dont need to add it because it already exists
				return _all_textures->at(i).second;
			}
		}
	}
	//add new if not exists
	Texture* t = new Texture(path, type, 0);
	_all_textures->push_back(std::pair<const char*, Texture*>{path, t});
	return t;
}


const Texture* Renderer::LoadTexture(const char* type, const char* path, unsigned int gl_slot) {
	//check if exissts
	for (int i = 0; i < _all_textures->size(); ++i) {
		const char* p = _all_textures->at(i).first;

		for (int j = 0; p[j] == path[j]; j++) {
			//if strings are identical
			if (p[j] == '\0' && path[j] == '\0') {
				//dont need to add it because it already exists
				return _all_textures->at(i).second;
			}
		}
	}
	//add new if not exists
	Texture* t = new Texture(path, type, gl_slot);
	_all_textures->push_back(std::pair<const char*, Texture*>{path, t});
	return t;
}

/// <summary>
/// what happens when your rendern ode has a basenode chld with its own children
/// </summary>
/// <param name="node"></param>
/// <param name="lastFbo"></param>
void Renderer::DrawNodes(BaseNode* node, RenderNode* lastFbo) {

	bool renderNode = Utility::IsRenderNode(node);
	bool isRoot = (node->GetParent() == NULL);
	const FBOComponent* fbo = NULL;
	RenderNode* nodeRn = NULL;

	if (renderNode) {
		//TURN ON RENDER NODES FBO
		TurnRenderNodeOn(nodeRn, node, fbo);
		//lastFbo = node;
	}

	//DRAW ALL THE CHILDREN TO THE CURRENTLY BOUND FBO
	const std::vector<BaseNode*>* children = node->GetAllChildren();
	RenderNode* rn = lastFbo;
	if (renderNode)
		rn = nodeRn;
	if (children != NULL) {
		for (int i = 0; i < children->size(); ++i) {
			
			//send child and last currently active fbo node
			DrawNodes(children->at(i), rn);

			//THE ALGORYTHM DRAWS ON ITS WAY OUT OF THE FUNCTION
		}
	}
	if (isRoot) {

		for (int i = 0; i < _extraDrawCalls->size(); i++) {
			(*_extraDrawCalls->at(i))();
		}
		DrawFinalRect(node, fbo);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	else {

		if (!renderNode) {
			//ACTUALLY DRAW THE NODE OT THE FBO ON THE WAY OUT OF THE FUNCTION
			auto  comps = node->Components();
			for (int i = 0; i < comps->size(); ++i) {
				if (comps->at(i)->second->IsGraphic()) {
					dynamic_cast<Graphic*>(comps->at(i)->second)->Draw(node->GetModelMatrix());
				}
			}

		}
		else if (renderNode) {
			//here it should turn itself off and the last parent render node in the hierarchy on
			//DRAW THE NODE OF THE CURRENTLY BOUND FBO TO ITS PARENT FBO which may or may not be final rect
			DrawRenderNode(lastFbo, nodeRn, fbo);
		}
	}
}


void Renderer::TurnRenderNodeOn(RenderNode*& rn, BaseNode* node, const FBOComponent*& fbo) {

	//fbo = node->GetComponent<FBOComponent>(FBOComponent::_component_id);
	//fbo = dynamic_cast<FBOComponent*>(node->GetAllChildren()->at(0));
	rn = dynamic_cast<RenderNode*>(node);
	fbo = rn->GetFBOComp();
	glBindFramebuffer(GL_FRAMEBUFFER, fbo->_fbo);
	fbo->Clear();
}


void Renderer::DrawRenderNode(const RenderNode* parent, const RenderNode* node, const FBOComponent* fbo) {
	
	//												SET UP FBO
	//unbind prev FBO
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	//ifi t is a render node but not the root node bind the FBO of the last FBO node
	glBindFramebuffer(GL_FRAMEBUFFER, parent->GetFBOComp()->_fbo);
	
	//												DRAW 
	//_fboMat->Bind(node->GetModelMatrix());
	node->GetMaterial()->Bind(node->GetModelMatrix());
	//bind texture from FBO
	unsigned int tId = fbo->_fboTexture;

	glBindTexture(GL_TEXTURE_2D, tId);
	//maybe this part is optioNAL because in the example above he doesnt use this
	// NOT ONLY IS IT OPTIONAL IT ALSO BREAKS THE CODE
	//glUniform1i(glGetUniformLocation(_fboMat->GetShader()->ID, "tex0"), fbo->_fboTexture); //maybe this part is optioNAL
	//t->Bind();
	_vao->Bind();

	//draw triangles
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	//												CLEAN
	parent->GetMaterial()->Unbind();
}


void Renderer::DrawFinalRect(const BaseNode* node, const FBOComponent* fbo) {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	//FBOComponent* f = node->GetAllChildren()->at(0)->GetComponent<FBOComponent>();
	//DRAW ROOT TO FINLal RECT

	_fRect->Bind();
	glDisable(GL_DEPTH_TEST);
	glBindTexture(GL_TEXTURE_2D, fbo->_fboTexture);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	_fRect->Unbind();
	glBindTexture(GL_TEXTURE_2D, 0);
}




Matrix4x4* Renderer::GetUIProjection() {
	return &_uiProjection;
}

Matrix4x4* Renderer::GetProjection() {
	return &_projection;
}
Camera* Renderer::GetCamera() {
	return _camera;
}


void Renderer::AddDrawCall(std::function<void()>* call) {

	_extraDrawCalls->push_back(call);

}