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
	std::vector< std::pair< const unsigned int, const BaseComponent*>*>* _components;
	BaseNode* _parent;
	std::vector<BaseNode*>* _children;
	bool _inheritTransform[3]{ true, true, true };
	bool _visible;
	Matrix4x4 _model;
	void Update(float deltaTime);
	const unsigned int _size;
public:
	BaseNode();
	BaseNode(Vec3 pos, Vec3 size, float ang);
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
	Matrix4x4* GetModelMatrix();
	void SetEnabled(bool on);

	const unsigned int AddChild(BaseNode* child);
	BaseNode* GetChild(const unsigned int id);
	void SetParent(BaseNode* parent);
	BaseNode* GetParent();
	const std::vector<BaseNode*>* GetAllChildren();


	template<class T> void AddComponent(const T* comp) const {
		const unsigned int size = sizeof(T);
		const bool exists = CheckIfComponentExists(size);

		if (exists) return;
		//const BaseComponent* b = new v1_6::Sprite();
		const BaseComponent* b = dynamic_cast<const BaseComponent*> (comp);
		std::pair<const  unsigned int, const BaseComponent*>* pair
			= new std::pair< const unsigned int, const BaseComponent*>({ size, b });
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
	template<class T> const T* GetComponent() const {
		unsigned int size = sizeof(T);
		T* comp = NULL;
		for (int i = 0; i < _components->size(); ++i) {
			if (_components->at(i)->first == size) {
				return  dynamic_cast<const T*>(_components->at(i)->second);
			}
		}
		return comp;
	}
	template<class T> const T* GetComponent(const unsigned int size) const {
		T* comp = NULL;
		for (int i = 0; i < _components->size(); ++i) {
			if (_components->at(i)->first == size) {
				return  dynamic_cast<const T*>(_components->at(i)->second);
			}
		}
		return comp;
	}
};

#endif
/*
	vector<pair<uint,BaseComponent*>*> components;

		template<T> void AddComponent(t){
			uint size = sizeof(t);
			bool exists = CheckIfComponentExists(size);

			if(exists) return;

			pair* p = new pair<uint, BaseComponent*>();
			p.first = size;
			p.second = t;

			components->add(t);
		}

		bool CheckCheckIfComponentExists(uint){
			foreach pair p in components:
				if p->first == uint:
					return true;

			return false;
		}

		template<T>  t GetComponent(){
			uint size = sizeof(T);
			foreach pair p in components:
				if p.first == size
					return p.second;

			return NULL;
		}

		template<T>  t GetComponent(uint size){
			foreach pair p in components:
				if p.first == size
					return p.second;

			return NULL;
		}
		void Update(float deltaTime){}
		void Draw(){}
	};

*/

/*

	- ITS A MIRACLE YOU HEARD THAT.
	- dIDDNT HEAR WHEN IT HAPPENS THOUGH
	- THIS YEAR

*/