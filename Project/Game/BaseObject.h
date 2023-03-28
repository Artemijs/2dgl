#ifndef BASEOBJECT_H
#define BASEOBJECT_H
#include "../Math/Matrix4x4.h"
#include "../Util/Callback.h"
#include <vector>


struct Transform {
public:
	Vec3 _position;
	Vec3 _scale;
	Vec3 _angle;
};





class BaseUpdate {
protected:
	bool _enabled;
public :
	BaseUpdate();
	virtual void TryUpdate(float deltaTime) = 0;
	virtual void Update(float deltaTime) = 0;
	//turns the object on/off, if off then it does not draw or update
	virtual void SetEnabled(bool enabled) = 0;
	bool GetEnabled();
};



class BaseObject : public BaseUpdate{
protected:
	int _nodeType;
	bool _inheritTransform[3]{ true, true, true };
	bool _visible;
	Transform _transform;
	Matrix4x4 _model;
	BaseObject* _parent;
	std::vector<BaseObject*>* _children;
	std::vector<BaseCall*>* _onMakeModelCalls;

private:
	void Update(float deltaTime);
public :
	BaseObject();
	BaseObject(Vec3 pos, Vec3 scale, Vec3 ang, BaseObject* parent = NULL, int nodeType = 0);
	~BaseObject();
	void TryUpdate(float deltaTime);
	/// <summary>
	/// sets _inheritTransform[id] to on/off, if on it does not move/scale/rotate with parent, nor do the children of this obj
	/// </summary>
	/// <param name="id"> int, 0 : position, 1 : scale, 2 : ang</param>
	/// <param name="on">true/false</param>
	void SetInheritTransform(int id, bool on);
	virtual void MakeModelMatrix(Matrix4x4 trans, Matrix4x4 scale, Matrix4x4 rot);
	//returns global positions rotation and scale
	Transform GetTransform();
	//set local posiion unless inherit transform of parent is off
	void SetPosition(Vec3 pos);
	//set local sale unless inherit transform of parent is off
	void SetScale(Vec3 scale);
	//set local angle unless inherit transform of parent is off
	void SetAngle(Vec3 angle);

	//turns the objects visibility on/off, if off then it does not draw
	void SetVisible(bool visible);
	BaseObject* GetParent();
	BaseObject* GetChild(int id);
	void SetParent(BaseObject* bo);
	//once child is set, its parent is set automatically
	int AddChild(BaseObject* bo);
	void SetEnabled(bool on);
	void AddCallback(BaseCall* call, int type = 0);
	Matrix4x4* GetModelMatrix();
	/// <summary>
	/// t : 0 a node that does not get rendered
	/// t : 1 graphic node  
	/// t : 2 render ndoe 
	/// </summary>
	/// <param name="t"></param>
	int GetNodeType();
	/// <summary>
	/// t : 0 a node that does not get rendered
	/// t : 1 graphic node 
	/// t : 2 render ndoe
	/// </summary>
	/// <param name="t"></param>
	void SetNodeType(int t);
	template<class T> T* GetComponent() {
		return dynamic_cast<T*>(this);
	}

	const std::vector<BaseObject*>* GetAllChildren();

};
#endif