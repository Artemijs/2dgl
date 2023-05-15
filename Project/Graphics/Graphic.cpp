#include "Graphic.h"
#include "Renderer.h"
//_baseMaterial is supposed to be uninitialised
Graphic::Graphic(const unsigned int indexCount): BaseComponent(true),
	_indexCount(indexCount)
{
	Renderer::instance()->AddGraphic(this);
	
	
}

Graphic::~Graphic() {
	delete _baseMaterial;
	printf("delting graphic\n");
}
Graphic::Graphic(const Material* m, const unsigned int indexCount):
	_baseMaterial(m) ,
	_indexCount(indexCount),
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