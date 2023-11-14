#include "UIHandler.h"
#include "../Math/CollisionDetection.h"


std::vector<BasePanel*>* UIHandler::_panels = new std::vector<BasePanel*>();


BasePanel* UIHandler::GetPanel(const char* name, BaseNode* parent, Vec3 pos, Vec3 size) {
	BasePanel* bp = new BasePanel(name, parent, pos, size);
	_panels->push_back(bp);
	return bp;
}


void UIHandler::Update(const float deltaTime) {
	//check mouse intersection with every edge of every panel
	for (unsigned int i = 0; i < _panels->size(); i++) {
		
	}

}


void UIHandler::Clean() {
	for (int i = 0; i < _panels->size(); i++) {
		delete _panels->at(i);
	}
	delete _panels;
}