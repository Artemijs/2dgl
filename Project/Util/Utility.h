#ifndef UTILITY_H
#define UTILITY_H
#include "../Game/BaseNode.h"

class Game;
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
	static void PrintVector(const char* prefix, const Vec3& v);
	static void PrintVector(const char* prefix, const Vec2& v);
	static void ToLower(std::string& s);
	static float Deg2Rad(const float deg);
	static float Rad2Deg(const float rad);
	
};



Game* DevGetGameType(const unsigned int id = 69696969);


#endif
