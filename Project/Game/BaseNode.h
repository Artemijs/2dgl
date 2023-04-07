#ifndef BASEOBJECT_H
#define BASEOBJECT_H
#include "../Math/Matrix4x4.h"
#include "../Util/Callback.h"
#include <vector>
#include "BaseComponent.h"

struct Transform {
public:
	Vec3 _position;
	Vec3 _scale;
	Vec3 _angle;
};
	
class BaseNode {
private:
	std::vector< std::pair<const unsigned int, const BaseComponent*>*>* _components;
public :
	BaseNode();
	~BaseNode();
	template<class T> void AddComponent(const T comp) const;
	const bool CheckIfComponentExists(const unsigned int id) const;
	template<class T> const T GetComponent() const;
	template<class T> const T GetComponent(const unsigned int size) const;

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