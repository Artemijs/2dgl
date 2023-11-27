#ifndef BASENODE_H
#define BASENODE_H
#include "../Math/Matrix4x4.h"

struct Transform {
public:
	Vec3 _position;
	Vec3 _scale;
	Vec3 _angle;
};


class BaseUpdate {
protected:
	bool _enabled;
public:
	BaseUpdate() {
		_enabled = true;
	}
	virtual void TryUpdate(float deltaTime) = 0;
	virtual void Update(float deltaTime) = 0;
	//turns the object on/off, if off then it does not draw or update
	virtual void SetEnabled(bool enabled) = 0;
	bool GetEnabled() {
		return _enabled;
	}
};




#include <vector>
#include "BaseComponent.h"
#include "../Graphics/Sprite.h"


class BaseNode : public BaseUpdate {
protected:
	Transform _transform;
	std::vector< std::pair< const unsigned int, BaseComponent*>*>* _components;
	BaseNode* _parent;
	std::vector<BaseNode*>* _children;
	//0 position, 1 scale, 2 angle
	bool _inheritTransform[3]{ true, true, true };
	bool _visible;
	Matrix4x4 _model;
	void Update(float deltaTime);
	//const unsigned int _size;
public:
	BaseNode();
	BaseNode(const Vec3 pos, const Vec3 size, const float ang);
	BaseNode(const Vec3 pos, const Vec3 size, const Vec3 ang);
	~BaseNode();
	virtual void SetSize();
	//updates the object if visible and enabled
	void TryUpdate(float deltaTime);

	/// <summary>
	/// sets _inheritTransform[id] to on/off, if on it does not move/scale/rotate with parent, nor do the children of this obj
	/// </summary>
	/// <param name="id"> int, 0 : position, 1 : scale, 2 : ang</param>
	/// <param name="on">true/false</param>
	void SetInheritTransform(int id, bool on);
	void SetInheritTransform(bool pos = true, bool scale = true, bool angle = true);
	//expects and array of 3 bools, 0 : position, 1 : scale, 2 : ang
	void SetInheritTransform(const bool* three);

	virtual void MakeModelMatrix(const Matrix4x4 trans, const Matrix4x4 scale, const Matrix4x4 rot) ;

	//returns global positions rotation and scale
	Transform& GetTransform();

	//set local posiion unless inherit transform of parent is off
	void SetPosition(Vec3 pos);

	//set local sale unless inherit transform of parent is off
	void SetScale(Vec3 scale);
	
	//set local angle unless inherit transform of parent is off
	
	/// <summary>
	///set local angle unless inherit transform of parent is off
	///, use the y axis 
	/// </summary>
	/// <param name="angle"></param>
	void SetAngle(Vec3 angle);

	//turns the objects visibility on/off, if off then it does not draw
	void SetVisible(bool visible);
	const Matrix4x4* GetModelMatrix() const;
	void SetEnabled(bool on);

	const unsigned int AddChild(BaseNode* child);
	BaseNode* GetChild(const unsigned int id);
	void SetParent(BaseNode* parent);
	const BaseNode* GetParent() const;
	const std::vector<BaseNode*>* GetAllChildren() const;

	std::vector< std::pair< const unsigned int, BaseComponent*>*>* Components() const ;

	template<class T> void AddComponent( T* comp) {
		
		const bool exists = CheckIfComponentExists(T::_component_id);

		if (exists) return;
		//const BaseComponent* b = new v1_6::Sprite();
		BaseComponent* b = dynamic_cast<BaseComponent*> (comp);
		const unsigned int id = b->ID();
		std::pair<const  unsigned int, BaseComponent*>* pair
			= new std::pair< const unsigned int, BaseComponent*>({ id, b });
		_components->push_back(pair);
	}

	const bool CheckIfComponentExists(const unsigned int id) const {
		for (int i = 0; i < _components->size(); ++i) {
			if (_components->at(i)->first == id) {
				return true;
			}
		}
		return false;
	}
	template<class T> T* GetComponent() const {
		const unsigned int id = T::_component_id;
		T* comp = NULL;
		for (int i = 0; i < _components->size(); ++i) {
			if (_components->at(i)->first == id) {
				return  dynamic_cast<T*>(_components->at(i)->second);
			}
		}
		return comp;
	}



	//pass the type it needs for it to cast base comp to the obj you want
	//id is the static id every component has MouseEvent::_id
	template<class T> T* GetComponent(const  unsigned int id) const {
		T* comp = NULL;
		for (int i = 0; i < _components->size(); ++i) {
			if (_components->at(i)->first == id) {
				return  dynamic_cast<T*>(_components->at(i)->second);
			}
		}
		return comp;
	}
	const Graphic* GetGraphic() const;
};

#endif


/*

	- ITS A MIRACLE YOU HEARD THAT.
	- dIDDNT HEAR WHEN IT HAPPENS THOUGH
	- THIS YEAR

*/

/*
	class Memory{
	static 
	
	};
	
*/