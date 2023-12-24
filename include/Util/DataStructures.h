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
	SLNode<T>* _previous;
	unsigned int _length;
public:
	SLNode<T>* _head;
	SLNode<T>* _tail;
	;
	SLNode<T>* _current;
	SList() {
		_head = NULL;
		_tail = NULL;
		_current = NULL;
		_previous = NULL;
		_length = 0;
	}
	

	~SList() { 
		//i should be able to call this in a destructor and not worry about it
		auto next = _head;
		while (next != NULL) {
			next = next->_next;
			delete _head;
			_head = next;
		}
		_current = NULL;
		_previous = NULL;
	}
	/// <summary>
	/// changes _creent to next and returns true when finished traversing
	/// </summary>
	/// <returns></returns>
	bool Traverse(){

		//if already null due to deletion
		if (_current == NULL) {
			_current = _head;
			_previous = NULL;
			return true;
		}
		_previous = _current;
		_current = _current->_next;
		//signal that the traversal has not yet finished
		if (_current == NULL) {
			_current = _head;
			_previous = NULL;
			return true;
		}
		else {
			return false;
		}
		/*
			2024 jan 8th and we have won the lotto
			
		*/
	}


	/// <summary>
	/// send to MemoryManager::AddToGarbage(node); the current node BE SURE TO NEGATE THE TRAVERSE AS THIS MOVES THE NODE UP BY ONE
	/// </summary>
	void Pop() {
		//					delete head
		if (_current == _head) {
			MemoryManager::AddToGarbage(_current);
			_length--;
			//set new head value
			if (_head->_next != NULL) {
				_head = _head->_next;
				_current = _head;
			}
			else //if now size 0
			{
				_head = NULL;
				_current = NULL;
			}
		}
		//					delete tail
		else if (_current == _tail) {

			//							delete tail
			MemoryManager::AddToGarbage(_current);
			_length--;
			//
			_tail = _previous;
			_current = _head;

		}
		else {
			//				delete any other node
			_previous->_next = _current->_next;
			//							delete tail
			MemoryManager::AddToGarbage(_current);
			_length--;
			_current = _previous->_next;
		}

	}


	void Add(T value) {

		_length++;
		SLNode<T>* node = new SLNode<T>(value);
		if (_head == NULL) {
			_head = node;
			_tail = _head;
			_current = node;
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