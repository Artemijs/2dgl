#ifndef BASENODE_H
#define BASENODE_H
#include "../Math/Matrix4x4.h"
#include "../Util/Callback.h"
#include <vector>
#include "BaseComponent.h"

/*struct Transform {
public:
	Vec3 _position;
	Vec3 _scale;
	Vec3 _angle;
};*/
	
class BaseNode {
private:
	std::vector< std::pair< const unsigned int, const BaseComponent*>*>* _components;
public :
	BaseNode();
	~BaseNode();

	template<class T> void AddComponent(const T* comp) const {
		const unsigned int size = sizeof(T);
		const bool exists = CheckIfComponentExists(size);

		if (exists) return;

		std::pair<const  unsigned int, const BaseComponent*>* pair = new std::pair< const unsigned int, const BaseComponent*>(size, NULL );
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
				return _components->at(i)->second;
			}
		}
		return comp;
	}
	template<class T> const T* GetComponent(const unsigned int size) const {
		T* comp = NULL;
		for (int i = 0; i < _components->size(); ++i) {
			if (_components->at(i)->first == size) {
				return _components->at(i)->second;
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