#include "BaseNode.h"
#include <iostream>

BaseNode::BaseNode():_size(0) {
	_components = new std::vector<std::pair<const unsigned int, const BaseComponent*>*>();
	_transform = { Vec3(), Vec3(), Vec3() };
	_parent = NULL;
	_children = new std::vector<BaseNode*>();
	_enabled = true;
	_visible = true;
	_model = Matrix4x4(1.0f);
}

BaseNode::BaseNode(Vec3 pos, Vec3 size, float ang):_size(0) {
	printf("creaating basenode\n");
	_components = new std::vector<std::pair<const unsigned int, const BaseComponent*>*>();
	_transform = { pos, size, Vec3(0, ang, 0) };
	_parent = NULL;
	_children = new std::vector<BaseNode*>();
	_enabled = true;
	_visible = true;
	_model = Matrix4x4(1.0f);
}
void BaseNode::SetSize() {
	printf("setting size in base\n");

}
BaseNode::~BaseNode() {
	printf("deleting basenode\n");
	for (int i = 0; i < _components->size(); i++) {
		delete _components->at(i)->second;
		delete _components->at(i);
	}
	delete _components;
	_parent = NULL;
	for (auto i = 0; i < _children->size(); ++i) {
		delete _children->at(i);
	}
	delete _children;
}


void BaseNode::TryUpdate(float deltaTime) {
	if (!_enabled)return;
	Update(deltaTime);
	for (int i = 0; i < _children->size(); ++i) {
		_children->at(i)->TryUpdate(deltaTime);
	}
}
void BaseNode::Update(float deltaTime) {
	return;
}

void BaseNode::SetInheritTransform(int id, bool on) {
	_inheritTransform[id] = on;
}

void BaseNode::MakeModelMatrix(Matrix4x4 trans, Matrix4x4 scale, Matrix4x4 rot) {
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
		_children->at(i)->MakeModelMatrix(nt, ns, nr);
	}

	_model = nt * nr * ns;
	/*for (int i = 0; i < _onMakeModelCalls->size(); ++i) {
		_onMakeModelCalls->at(i)->Execute();
	}*/
}



Transform BaseNode::GetTransform() {
	return _transform;
}

void BaseNode::SetPosition(Vec3 pos) {
	_transform._position = pos;
}

void BaseNode::SetScale(Vec3 scale) {
	_transform._scale = scale;
}

void BaseNode::SetAngle(Vec3 angle) {
	_transform._angle = angle;
}


void BaseNode::SetVisible(bool visible) {
	_visible = visible;
	/*for (int i = 0; i < _children->size(); ++i) {
		_children->at(i)->SetVisible(visible);
	}*/
}

void BaseNode::SetEnabled(bool enabled) {
	_enabled = enabled;
	for (int i = 0; i < _children->size(); ++i) {
		_children->at(i)->SetEnabled(enabled);
	}
}
Matrix4x4* BaseNode::GetModelMatrix() { return &_model; }
const unsigned int BaseNode::AddChild(BaseNode* child) {
	const unsigned int id = _children->size();
	_children->push_back(child);
	return id;
}
BaseNode* BaseNode::GetChild(const unsigned int id) {
	return _children->at(id);
}
const std::vector<BaseNode*>* BaseNode::GetAllChildren() {
	return _children;
}
void BaseNode::SetParent(BaseNode* parent) {
	_parent = parent;
}
BaseNode* BaseNode::GetParent() {
	return _parent;
}
//28 