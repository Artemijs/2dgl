#ifndef DATA_STRUCTS_H
#define DATA_STRUCTS_H
#include <iostream>
#include "Util/MemoryManager.h"




template <typename T> class SLNode : public Memory{
public:
	T _value;
	SLNode<T>* _next;
	
	SLNode() :_next(NULL), _value(NULL) {}
	SLNode(T value = NULL, SLNode<T>* next = NULL) : _next(next), _value(value) { }
	~SLNode() override  {
		std::cout << "DELETING node from list\n";
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
		//i should be able to call this in a destructor and not worry about it
		auto next = _head->_next;
		while (next != NULL) {
			delete _head;
			_head = next;
		}
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