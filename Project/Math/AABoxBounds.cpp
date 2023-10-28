/*#include "AABoxBounds.h"




AABoxBounds::AABoxBounds(BaseNode* owner) : BoxBounds(owner){

	_localRect[0] = Vec3(-0.5f,		0.5f,	0.0f);
	_localRect[1] = Vec3(0.5f,		0.5f,	0.0f);
	_localRect[2] = Vec3(-0.5f,		-0.5f,	0.0f);
	_localRect[3] = Vec3(0.5f,		-0.5f,	0.0f);
	//_type = BoundsType::AABB;
}


AABoxBounds::AABoxBounds(BaseNode* owner, const Vec3 topLeft, const Vec3 topRight, const Vec3 botLeft, const Vec3 botRight):
	BoxBounds(owner, BoundsType::AABB) {

	_localRect[0] = topLeft;
	_localRect[1] = topRight;
	_localRect[2] = botLeft;
	_localRect[3] = botRight;
	_type = BoundsType::AABB;

}*/