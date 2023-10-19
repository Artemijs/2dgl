#ifndef UTILITY_H
#define UTILITY_H
#include "../Game/BaseNode.h"

class Game;
class Utility {
public:
	static unsigned int _idCount;
	
	
	template<class T> static const unsigned int GetID() {
		int sum = 0;
		const char* c = typeid(T).name();
		char cv = *(c);
		while (*(c) != '\0') {
			sum += (int)*(c);
			c += sizeof(*(c));
		}
		return sum;
	}
	static const unsigned int GetID();
	static const unsigned int GetMouseEventID();
	static bool IsRenderNode(const BaseNode* node) ;


	static const float Dist2CLosest(const float min, const float max, const float p);
	static void PrintVector(const char* prefix, const Vec3& v);
	static void PrintVector(const char* prefix, const Vec2& v);
	static void ToLower(std::string& s);
	static float Deg2Rad(const float deg);
	static float Rad2Deg(const float rad);
	
};



Game* DevGetGameType(const unsigned int id = 69696969);


#endif

#ifndef SLINKED_LIST
#define SLINKED_LIST
template <typename T> class SLNode {
public:
	
	SLNode<T>* _next;
	T* _value;
	SLNode() :_next(NULL), _value(NULL) {}
	SLNode(T* value = NULL, SLNode<T>* next = NULL): _next(next), _value(value) { }
};


template <typename T> class SList {
public:
	SLNode<T>* _head;
	SLNode<T>* _tail;
	SList() {
		_head = NULL;
		_tail = NULL;
	}
	void Add(T node) {

		/*SLNode<T> n = SLNode<T>(node);
		if (_head == NULL) {
			_head = n;
			_tail = _head;
		}
		else {
			_tail->_next = &n;
			_tail = n;
		}*/
	}
};
#endif