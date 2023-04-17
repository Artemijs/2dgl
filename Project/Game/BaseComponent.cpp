#include "BaseComponent.h"
#include <iostream>
BaseComponent::BaseComponent() :_isGraphic(false){
	
}
BaseComponent::~BaseComponent() {
	printf("deleting base comonent\n");
}
const bool BaseComponent::IsGraphic() {
	return _isGraphic;
}