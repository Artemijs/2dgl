#include "Utility.h"
#include "../Game/FBOComponent.h"

const unsigned int Utility::_fboCompSize = sizeof(FBOComponent);
unsigned int Utility::_idCount = 0;

bool Utility::IsRenderNode(const BaseNode* node) {
	auto components = node->Components();
	if (components->size() != 1) return false;
	return (components->at(0)->first == _fboCompSize);
}