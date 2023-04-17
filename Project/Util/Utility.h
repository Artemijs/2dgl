#ifndef UTILITY_H
#define UTILITY_H
#include "../Game/BaseNode.h"
class Utility {
public:
	static unsigned int _idCount;
	
	template<class T> static const unsigned int GetID() {
		return _idCount+=1;
	}
	static const unsigned int GetID() {
		return _idCount += 1;
	}
	static bool IsRenderNode(const BaseNode* node) ;
};

#endif