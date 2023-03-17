#include "Element.h"

Element::Element() {
	_children = new std::vector<Element*>();
	_parent = NULL;
}
Element::Element(Element* parent) {
	_children = new std::vector<Element*>();
	_parent = parent;
}
Element::~Element() {
	delete _children;
}
int Element::AddChild(Element* child) {
	_children->push_back(child);
	child->SetParent(this);
	return _children->size() - 1;
}
void Element::SetParent(Element* parent) {
	_parent = parent;
}
Element* Element::GetChild(int id) {
	return _children->at(id);
}

Element* Element::GetParent() {
	return _parent;
}