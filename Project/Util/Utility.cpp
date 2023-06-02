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
const float Utility::Dist2CLosest(const float min, const float max, const float p) {
	const float min_m_p = min - ((p - min) * 2);
	const float max_m_p = max - p;
	if (min_m_p < max_m_p) {
		return min_m_p;
	}
	else
		return max_m_p;
}

void Utility::PrintVector(const char* prefix, const Vec3& v) {
	std::cout << prefix << "(" << v.x << " ," << v.y << " ," << v.z << ")\n";
}
void Utility::PrintVector(const char* prefix, const Vec2& v) {
	std::cout << prefix << "(" << v.x << " ," << v.y <<  ")\n";
}
/*
	a = 10 
	b = 20 
	c = 13
	a - c =  -3
	b - c =  7 

	a = 1
	b = 25
	c = 23
	a - c =  -22
	b - c =  2

*/