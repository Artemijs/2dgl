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
	/// <summary>
	/// checks if the first component of the object is an FBOComponent since it is always the first and usually only component that a render node has
	/// </summary>
	/// <param name="node"></param>
	/// <returns></returns>
	static bool IsRenderNode(const BaseNode* node) ;


	static const float Dist2CLosest(const float min, const float max, const float p);
	static void PrintVector(const char* prefix, const Vec3& v);
	static void PrintVector(const char* prefix, const Vec2& v);
	static void ToLower(std::string& s);
	static float Deg2Rad(const float deg);
	static float Rad2Deg(const float rad);
	/// <summary>
	/// put elements of b, starting at start into a and a into b
	/// no index out of bounds check
	/// </summary>
	/// <param name="a">float array a</param>
	/// <param name="b">float array b</param>
	/// <param name="start">start position of data</param>
	/// <param name="len">len of data swapped</param>
	static void Swap(float* a, float* b, const int start, const int len);
	static void Swap(float* data, const int startA, const int startB, const int len);
};



Game* DevGetGameType(const unsigned int id = 69696969);


#endif
