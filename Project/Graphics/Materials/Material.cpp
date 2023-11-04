#include "Material.h"
#include "../Renderer.h"




/// <summary>
/// loads the default shader 0 
/// </summary>
BaseMaterial::BaseMaterial():
	_transparent(false),
	_shader(Renderer::instance()->GetShader(0)),
	_color(Vec4(1.0f, 1.0f, 1.0f, 1.0f)),
	Memory(){
	
}


BaseMaterial::BaseMaterial(const Shader* s) :
	_transparent(true),
	_shader(s),
	_color(Vec4(1.0f, 1.0f, 1.0f, 1.0f)),
	Memory(){

}


BaseMaterial::~BaseMaterial() {
	
}


void BaseMaterial::Bind(const Matrix4x4* model) const {

	_shader->Activate();
	glUniformMatrix4fv(glGetUniformLocation(_shader->ID, "model"), 1, GL_TRUE, &model->buff[0]);
	glUniform4f(glGetUniformLocation(_shader->ID, "color"), _color.x, _color.y, _color.z, _color.a);

}


void BaseMaterial::Unbind()const {
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glUseProgram(0);

}


const Shader* BaseMaterial::GetShader() const { return _shader; }



//														MATERIAL
//---------------------------------------------------------------------------------------------------



Material::Material() :
	BaseMaterial(Renderer::instance()->GetShader(1)),
	_textures( new std::vector<const Texture*>()){
	_textures->push_back(Renderer::instance()->LoadTexture("tex0", "Assets/Textures/default.png"));
	
}


Material::Material(const Shader* s, const char* texturePath) : 
	BaseMaterial(s), _textures(new std::vector<const Texture*>()) {
	_textures->push_back(Renderer::instance()->LoadTexture("tex0", texturePath));

}


Material::~Material() {
	printf("deleting material base\n");
	delete _textures;
}


std::vector<const Texture*>* Material::GetTexture() const {
	return _textures;
}


/// <summary>
/// some optimisation can be added here if you have shader variables that dont change they can be bound once only
/// </summary>
/// <param name="model"></param>
void Material::Bind(const Matrix4x4* model) const {
	BaseMaterial::Bind(model);
	Renderer::instance()->SetShaderVariables(_shader->ID);
	for (int i = 0; i < _textures->size(); i++) {
		const Texture* t = _textures->at(i);
		t->Bind();
		t->texUni(_shader, 0);
	}

}


void Material::Unbind()const {
	BaseMaterial::Unbind();
	
}

void Material::AddTexture(const char* name, const char* filePath) {
	_textures->push_back(Renderer::instance()->LoadTexture(name, filePath));
}



//										MATERIAL UI NO TEXTURE
//------------------------------------------------------------------------------




MaterialUI::MaterialUI():  BaseMaterial(Renderer::instance()->GetShader(1)),
_texture(Renderer::instance()->LoadTexture("text0", "Assets/Textures/default.png")) {

}


MaterialUI::MaterialUI(const Shader* s, const char* texturePath) :
	BaseMaterial(s), _texture(Renderer::instance()->LoadTexture("text0", texturePath)) {
	
}


MaterialUI::~MaterialUI() {

	printf("deleting material base\n");

}


void MaterialUI::Bind(const Matrix4x4* model) const {
	BaseMaterial::Bind(model);

	_texture->Bind();
	_texture->texUni(_shader, 0);
	glUniformMatrix4fv(glGetUniformLocation(_shader->ID, "proj"), 1, GL_TRUE, &Renderer::instance()->GetUIProjection()->buff[0]);

}


void MaterialUI::Unbind()const {
	BaseMaterial::Unbind();
}


const Texture* MaterialUI::GetTexture() const {
	return _texture;
}


//										MATERIAL UI NO TEXTURE
//------------------------------------------------------------------------------



MaterialUiNoTex::MaterialUiNoTex() : BaseMaterial(Renderer::instance()->GetShader(1)) {

}


MaterialUiNoTex::MaterialUiNoTex(const Shader* s) :
	BaseMaterial(s) {

}


MaterialUiNoTex::~MaterialUiNoTex() {

	printf("deleting material base\n");

}


void MaterialUiNoTex::Bind(const Matrix4x4* model) const {
	BaseMaterial::Bind(model);
	glUniformMatrix4fv(glGetUniformLocation(_shader->ID, "proj"), 1, GL_TRUE, &Renderer::instance()->GetUIProjection()->buff[0]);

}


void MaterialUiNoTex::Unbind()const {
	BaseMaterial::Unbind();
}


