#include "Utility.h"
#include "../Game/FBOComponent.h"


unsigned int Utility::_idCount = 0;

bool Utility::IsRenderNode(const BaseNode* node) {
	const unsigned int fboCompSize = FBOComponent::_id;
	auto components = node->Components();
	if (components->size() != 1) return false;
	return (components->at(0)->first == fboCompSize);
}