#ifndef UTILITY_H
#define UTILITY_H
#include "../Game/BaseNode.h"

class Utility {
public:
	static unsigned int _idCount;
	
	
	template<class T> static const unsigned int GetID() {
		int sum = 0;
		const char* c = typeid(T).name();
		char cv = *(c);
		while (*(c) != '\0') {
			sum += (int)*(c);
			c += sizeof(*(c));
		}
		return sum;
	}
	static const unsigned int GetID();
	static const unsigned int GetMouseEventID();
	static bool IsRenderNode(const BaseNode* node) ;


	static const float Dist2CLosest(const float min, const float max, const float p);
};

#endif