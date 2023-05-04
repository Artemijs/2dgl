#include "Utility.h"
#include "../Game/FBOComponent.h"
#include "../Game/Game.h"

unsigned int Utility::_idCount = 0;
bool Utility::IsRenderNode(const BaseNode* node) {
	const unsigned int fboCompSize = FBOComponent::_id;
	auto components = node->Components();
	if (components->size() != 1) return false;
	return (components->at(0)->first == fboCompSize);
}

const unsigned int Utility::GetID() 
{
	//id = sacii sum of type_info.name
	printf("mouse event of type Game id : %d \n", MouseEvent<Game>::_id);
	_idCount++;
	return _idCount;
	
}
const unsigned int Utility::GetMouseEventID() {
	//const unsigned int mId = MouseEvent<Game>::_id;
	
	int sum = 0;
	const char* c = typeid(MouseEvent<Game>).name();
	char cv = *(c);
	while (*(c) != '\0') {
		std::cout << *(c) << "\n";
		sum += (int)*(c);
		c += sizeof(*(c));
	}
	return sum;
}