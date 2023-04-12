#include "RenderNode.h"
#include "../Graphics/Renderer.h"
#include "../Game/Game.h"
#include "../Game/BaseNode.h"


RenderNode::RenderNode() :
	BaseNode(Vec3(), Renderer::instance()->WindowSizeVec3(), 0),
	_fbo(new FBO(Renderer::instance()->WindowSizeVec3().x, Renderer::instance()->WindowSizeVec3().y)) {
	//_fbo = FBO();

}

//uses default image as background
RenderNode::RenderNode(Vec3 pos, Vec3 size, float ang) :
	BaseNode(pos, size,  ang), _fbo(new FBO(size.x, size.y)) {
	//_fbo = FBO();
}
RenderNode::~RenderNode() {
	std::cout << "RENDER NODE DELETED\n";
	delete _fbo;
}
void RenderNode::MakeModelMatrix(Matrix4x4 trans, Matrix4x4 scale, Matrix4x4 rot) {
	//std::cout << "MMM from render node\n";
	Matrix4x4 nt, ns, nr;
	if (_inheritTransform[0])
		nt = Matrix4x4::TranslationMatrix(_transform._position) * trans;
	else
		nt = Matrix4x4::TranslationMatrix(_transform._position);

	if (_inheritTransform[1])
		ns = Matrix4x4::ScaleMatrix(_transform._scale) * scale;
	else
		ns = Matrix4x4::ScaleMatrix(_transform._scale);

	if (_inheritTransform[2])
		nr = Matrix4x4::RotationMatrix(_transform._angle.y) * rot;
	else
		nr = Matrix4x4::RotationMatrix(_transform._angle.y);

	for (int i = 0; i < _children->size(); ++i) {
		_children->at(i)->MakeModelMatrix(Matrix4x4(1.0f), Matrix4x4(1.0f), Matrix4x4(1.0f));
	}

	_model = nt * nr * ns;
}
const FBO* RenderNode::GetFBO()const {
	return _fbo;
}




/*
	when FBOs texture is smaller than the screen
		- when rendered to final rect ti gets scaled
	MY ASSUMPTIONS ARE
	IF I DRAW EVERY UI ELEMENT OF A WINDOW TO THAT WINDOW THEN DRAW THE WINDOW AS A TEXTURE THAT COVERS THE WHOLE SCREEN
		THEN OBVIOUSLY ENOUGH EACH UI MENU WINDOW(IE AN INVENTORY) WILL STRETCH OVER THE WHOLE SCREEN
	//but this is only for the root node 

*/