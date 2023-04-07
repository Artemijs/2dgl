#include "BaseNode.h"
#include <iostream>

BaseNode::BaseNode() {}

BaseNode::~BaseNode() {}

template<class T> void BaseNode::AddComponent(const T comp) const {
	const unsigned int size = sizeof(T);
	const bool exists = CheckIfComponentExists(size);
	
	if (exists) return;
	
	const std::pair<const unsigned int, const BaseNode*>* pair = new std::pair<const unsigned int, const BaseNode*>();
	pair->first = size;
	pair->second = comp;
	_components->push_back(pair);
}
const bool BaseNode::CheckIfComponentExists(const unsigned int id) const {
	return true;
}
template<class T> const T BaseNode::GetComponent() const {
	return NULL;
}
template<class T> const T BaseNode::GetComponent(const unsigned int size) const {
	return NULL;
}

