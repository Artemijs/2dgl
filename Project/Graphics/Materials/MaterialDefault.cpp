#include "MaterialDefault.h"
#include "../Renderer.h"
MaterialDefault::MaterialDefault(): Material() {
	//_shader = Renderer::instance()->GetShader(0);
}
MaterialDefault::MaterialDefault(const Shader* s, const char* texturePath): Material(s, texturePath) {

}				
MaterialDefault::~MaterialDefault() {
	printf("deleting default material class\n");
}						
void MaterialDefault::Bind(const Matrix4x4* model)const  {
	//_shader->Activate();

	
	//glUniform4f(glGetUniformLocation(_shader->ID, "color"), _color.x, _color.y, _color.z, _color.a);
	//glUniformMatrix4fv(glGetUniformLocation(_shader->ID, "model"), 1, GL_TRUE, &model->buff[0]);
	//Renderer::instance()->SetShaderVariables(_shader->ID);
	//_texture->Bind();	
	//_texture->texUni(_shader, "tex0", 0);
	
	
	//Material::Bind(model);
	Material::Bind(model);
	Renderer::instance()->GetVAO()->Bind();
}						
						
void MaterialDefault::Unbind()const {
	Material::Unbind();

}