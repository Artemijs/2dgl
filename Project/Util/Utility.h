#ifndef UTILITY_H
#define UTILITY_H
#include "../Game/BaseNode.h"
class Utility {
public:
	const static unsigned int _fboCompSize;
	static bool IsRenderNode(const BaseNode* node) ;
};

#endif