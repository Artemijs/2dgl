#include "Game/RenderNode.h"
#include "Graphics/Renderer.h"
#include "Game/FBOComponent.h"
#include "UI/BasePanel.h"
#include "Math/Bounds.h"




RenderNode::RenderNode() :
	BaseNode( Vec3(),  Renderer::instance()->WindowSizeVec3(), 0) {
	AddFBO();
	RenderNodeMat* rnMat = new RenderNodeMat(Renderer::instance()->GetShader(8));
	rnMat->_borderColor = Vec4(1.0f, 1.0f, 1.0f, 1.0f);
	rnMat->_borderSize = 1.0f;
	rnMat->_textureSize = Vec2(100, 100);
	_nodeMat = rnMat;

}

//uses default image as background
RenderNode::RenderNode(const Vec3 pos, const Vec3 size, const float ang) :
	BaseNode(pos, size, ang){
	AddFBO();
	Renderer* r = Renderer::instance();
	_nodeMat = new RenderNodeMat(r->GetShader(8));

	RenderNodeMat* rnMat = new RenderNodeMat(r->GetShader(8));

	//Vec2 uvScale(size.x/r->GetWindowSize().x, size.y/r->GetWindowSize().y);
	
	//Vec2 uvScale(1,1);
	rnMat->_borderColor = Vec4(1.0f, 1.0f, 1.0f, 1.0f);
	rnMat->_borderSize = 1.0f;
	rnMat->_textureSize = Vec2(size.x, size.y);
	rnMat->RecalcUV(_transform);
	_nodeMat = rnMat;
	
}


void RenderNode::AddFBO() {
	//_fboComp = new FBOComponent(_transform._scale.x, _transform._scale.y);
	_fboComp = new FBOComponent();
	AddComponent<FBOComponent>(_fboComp);
	//_fboComp->SetClearColor(Vec3(0.1, 0.1, 0.1));
}


RenderNode::~RenderNode() {
	std::cout << "RENDER NODE DELETED\n";
	delete _nodeMat;
}

/// <summary>
/// the children of this node are always in projection space, scaling the node doesnt do anything
/// </summary>
/// <param name="trans"></param>
/// <param name="scale"></param>
/// <param name="rot"></param>
void RenderNode::MakeModelMatrix(const Matrix4x4 trans, const Matrix4x4 scale, const Matrix4x4 rot) {
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
		nr = Matrix4x4::RotationMatrix(_transform._angle) * rot;
	else
		nr = Matrix4x4::RotationMatrix(_transform._angle);

	for (int i = 0; i < _children->size(); ++i) {
		_children->at(i)->MakeModelMatrix(Matrix4x4(1.0f), Matrix4x4(1.0f), Matrix4x4(1.0f));
	}

	_model = nt * nr * ns;

	// CHECK TO SEE IF THE CHILDREN HAVE COLLISION BOXES AND MOVE THEM BY
	//		pos - size/2
	//check if children have bounds
	/*for (int i = 0; i < _children->size(); i++) {
		auto child = _children->at(i);
		Bounds* box = child->GetComponent<Bounds>(Bounds::_component_id);
		if (box != NULL) {
			//translate childrens bounds
			//OPTIMISATION NEEDED
			box->SetOffset(
				Matrix4x4::TranslationMatrix(Vec3(
					_transform._position.x - _transform._scale.x * 0.5f,
					_transform._position.y - _transform._scale.y * 0.5f,
					0.0f
				))
			);
		}
	}*/
}


const FBOComponent* RenderNode::GetFBOComp() const {
	return _fboComp;
}


void RenderNode::SetNodeMat(BaseMaterial* bm) {
	_nodeMat = bm;
}


BaseMaterial* RenderNode::GetMaterial()const  {
	return _nodeMat;
}