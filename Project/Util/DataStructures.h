#ifndef DATA_STRUCTS_H
#define DATA_STRUCTS_H
#include "MemoryManager.h"

template <typename T> class SLNode : public Memory{
public:

	SLNode<T>* _next;
	T _value;
	SLNode() :_next(NULL), _value(NULL) {}
	SLNode(T value = NULL, SLNode<T>* next = NULL) : _next(next), _value(value) { }
	~SLNode() override  {
		delete _value;
		//delete _next;
	}
};



template <typename T> class SList {
private:
	unsigned int _length;
public:
	SLNode<T>* _head;
	SLNode<T>* _tail;
	
	
	SList() {
		_head = NULL;
		_tail = NULL;
		_length = 0;
	}

	~SList() { 
		//DeleteEverything();
	}
	void Add(T value) {

		_length++;
		SLNode<T>* node = new SLNode<T>(value);
		if (_head == NULL) {
			_head = node;
			_tail = _head;
		}
		else {
			_tail->_next = node;
			_tail = node;
		}
	}


	void DeleteEverything() {
		if (_head == NULL) return;
		SLNode<T>* node = NULL;
		while (_head != NULL) {
			node = _head->_next;
			MemoryManager::AddToGarbage(_head);
			_length--;
			_head = node;	
		}
	}
	unsigned int  Size() { return _length; }
};
#endif