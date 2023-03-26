#include "BaseObject.h"
#include <iostream>

BaseObject::BaseObject() {
	_transform = { Vec3(), Vec3(), Vec3() };
	_enabled = true;
	_visible = true;
	_model = Matrix4x4(1.0f);
	_parent = NULL;
	_children = new std::vector<BaseObject*>();
	_onMakeModelCalls = new std::vector<BaseCall*>();
	_nodeType = 0;
}

BaseObject::BaseObject(Vec3 pos, Vec3 scale, Vec3 ang,BaseObject* parent, int nodeType) {
	_transform = { pos, scale, ang };
	_enabled = true;
	_visible = true;
	_model = Matrix4x4(1.0f);
	_parent = parent;
	_children = new std::vector<BaseObject*>();
	_onMakeModelCalls = new std::vector<BaseCall*>();
	_nodeType = nodeType;
}

BaseObject::~BaseObject() {
	delete _children;
	for (int i = 0; i < _onMakeModelCalls->size(); ++i) {
		delete _onMakeModelCalls->at(i);
	}
	delete _onMakeModelCalls;
}
void BaseObject::TryUpdate(float deltaTime) {
	if (!_enabled)return;
	Update(deltaTime);
	for (int i = 0; i < _children->size(); ++i) {
		_children->at(i)->TryUpdate(deltaTime);
	}
}
void BaseObject::Update(float deltaTime) {
	return;
}

void BaseObject::SetInheritTransform(int id, bool on) {
	_inheritTransform[id] = on;
}

void BaseObject::MakeModelMatrix(Matrix4x4 trans, Matrix4x4 scale, Matrix4x4 rot) {
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
	for (int i = 0; i < _onMakeModelCalls->size(); ++i) {
		_onMakeModelCalls->at(i)->Execute();
	}
}

Transform BaseObject::GetTransform() {
	return _transform;
}

void BaseObject::SetPosition(Vec3 pos) {
	_transform._position = pos;
}

void BaseObject::SetScale(Vec3 scale) {
	_transform._scale = scale;
}

void BaseObject::SetAngle(Vec3 angle) {
	_transform._angle = angle;
}


void BaseObject::SetVisible(bool visible) {
	_visible = visible;
	for (int i = 0; i < _children->size(); ++i) {
		_children->at(i)->SetVisible(visible);
	}
}

BaseObject* BaseObject::GetParent() {
	return _parent;
}

BaseObject* BaseObject::GetChild(int id) {
	return _children->at(id);
}

int BaseObject::AddChild(BaseObject* bo) {
	if (bo == NULL) return -1;
	bo->SetParent(this);
	_children->push_back(bo);
	return _children->size() - 1;
}

void BaseObject::SetParent(BaseObject* bo) {
	_parent = bo;
}

void BaseObject::SetEnabled(bool enabled) {
	_enabled = enabled;
	for (int i = 0; i < _children->size(); ++i) {
		_children->at(i)->SetVisible(enabled);
	}
}

void BaseObject::AddCallback(BaseCall* call, int type ) {
	_onMakeModelCalls->push_back(call);
}
Matrix4x4* BaseObject::GetModelMatrix() { return &_model; }
/// <summary>
	/// t : 0 render ndoe 
	/// t : 1 graphic node  
	/// t : 2 a node that does not get rendered
	/// </summary>
	/// <param name="t"></param>
int BaseObject::GetNodeType() { return _nodeType; }
/// <summary>
/// t : 0 render ndoe
/// t : 1 graphic node 
/// t : 2 a node that does not get rendered
/// </summary>
/// <param name="t"></param>
void BaseObject::SetNodeType(int t) { _nodeType = t; }


BaseUpdate::BaseUpdate() {
	_enabled = true;
}
bool BaseUpdate::GetEnabled() { return _enabled; }



/*
REDESIGN THE OBJECT INHRITANCE
	THE PROBLEM: 
		cant access in herited classes and functionality from base class
	EXAMPLE
		Go through each base object in a branch and disable collision


class BaseObject{
	List<Attachment> _attachments;
	void AddAttachment(BaseAttachment* a);
}

class BaseAttachment{

};

class MouseEvent: public BaseAttachment{}
class ObjectFactory{

	BaseObject MakeSprite(vec3 pos, vec3 size, ang){
		BaseObject* b = new BaseObject(pos, size, ang);
		b->addAttachment(new Sprite("Assets/path/img.png"));
		b->addAttachment(new MouseEvent());
		return b;
	}
};


class MouseEventAttachment: public BaseAttachment{
	
	MouseEvent* m;


	MouseEventAttachment(){
	
	}
	~MouseEventAttachment();

};

class MouseEvent {
protected:
	Bounds* _bounds;

public:
	MouseEvent(Bounds* bounds, BaseObject* bo);
	virtual void OnMouseEnter(const Vec2* mPos) = 0;
	virtual void OnMouseLeave(const Vec2* mPos) = 0;
	//these need to be rewritten
	virtual void OnPressed(const Vec2* mpos) = 0;
	virtual void OnReleased(const Vec2* mpos) = 0;
	virtual void OnClick(const Vec2* mPos) = 0;

	virtual void OnDoubleClick(const Vec2* mPos) = 0;
	virtual void OnHover(const Vec2* mPos) = 0;
	virtual void OnEndHover(const Vec2* mPos) = 0;
	Bounds* GetBounds() { return _bounds; }

};


A DIFFERENT SOLUTION
struct OBJ{
	int _type;
	int _id;
};
 int[][];
 
 BaseObject{
	std::vector<OBJ>* _allComponents;
	AddComponent(OBJ){
		_allComponents->push_back(CoponentFactory::GetComponent(&OBJ));
	}
 };











*/