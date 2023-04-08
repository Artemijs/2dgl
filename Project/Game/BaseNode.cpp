#include "BaseNode.h"
#include <iostream>

BaseNode::BaseNode() {
	_components = new std::vector<std::pair<const unsigned int, const BaseComponent*>*>();
}

BaseNode::~BaseNode() {
	for (int i = 0; i < _components->size(); i++) {
		delete _components->at(i)->second;
		delete _components->at(i);
	}
	delete _components;
}

/*template<class T> void BaseNode::AddComponent()  {
	const unsigned int size = sizeof(T);
	const bool exists = CheckIfComponentExists(size);
	
	if (exists) return;
	
	const std::pair<const unsigned int, const BaseComponent*>* pair = new std::pair<const unsigned int, const BaseComponent*>();
	pair->first = size;				
	pair->second = comp;			
	_components->push_back(pair);	
}*/

/*
const bool BaseNode::CheckIfComponentExists(const unsigned int id) const {
	
	for (int i = 0; i < _components->size(); ++i) {
		if (_components->at(i)->first == id) {
			return true;
		}
	}
	return false;
}
template<class T> const T BaseNode::GetComponent() const {
	unsigned int size = sizeof(T);
	T* comp = NULL;
	for (int i = 0; i < _components->size(); ++i) {
		if (_components->at(i)->first == size) {
			return _components->at(i)->second;
		}
	}
	return comp;
}
template<class T> const T BaseNode::GetComponent(const unsigned int size) const {
	T* comp = NULL;
	for (int i = 0; i < _components->size(); ++i) {
		if (_components->at(i)->first == size) {
			return _components->at(i)->second;

		}
	}
	return comp;
}

*/