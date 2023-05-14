#include "Graphic.h"
#include "Renderer.h"
Graphic::Graphic(): BaseComponent(true) {
	Renderer::instance()->AddGraphic(this);
	
	
}

Graphic::~Graphic() {
	delete _baseMaterial;
	printf("delting graphic\n");
}
Graphic::Graphic(const Material* m):
	_baseMaterial(m) ,
	BaseComponent(true)	{
	Renderer::instance()->AddGraphic(this);

}
void Graphic::Draw(const Matrix4x4* model) const {
 	_baseMaterial->Bind(model);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	_baseMaterial->Unbind();
}
	
const Material* Graphic::GetMaterial() const {
	return _baseMaterial;
}