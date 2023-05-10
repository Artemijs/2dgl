#include "Utility.h"
#include "../Game/FBOComponent.h"
#include "../Game/Game.h"

unsigned int Utility::_idCount = 0;
bool Utility::IsRenderNode(const BaseNode* node) {
	const unsigned int fboCompSize = FBOComponent::_component_id;
	auto components = node->Components();
	if (components->size() != 1) return false;
	return (components->at(0)->first == fboCompSize);
}

const unsigned int Utility::GetID() 
{
	//id = sacii sum of type_info.name
	_idCount++;
	return _idCount;
	
}