#include "Game/BaseComponent.h"
#include <iostream>
BaseComponent::BaseComponent() :_isGraphic(false){
	
}
BaseComponent::BaseComponent(bool isGraphic) : _isGraphic(isGraphic) {

}
BaseComponent::~BaseComponent() {
	printf("deleting base comonent\n");
}
const bool BaseComponent::IsGraphic()const {
	return _isGraphic;
}