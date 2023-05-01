#include "BoxBounds.h"
BoxBounds::BoxBounds() {

	_localRect[0] = Vec3(-0.5f, 0.5f, 0.1f);
	_localRect[1] = Vec3(0.5f, 0.5f, 0.1f);
	_localRect[2] = Vec3(-0.5f, -0.5f, 0.1f);
	_localRect[3] = Vec3(0.5f, -0.5f, 0.1f);
}
BoxBounds::BoxBounds(Vec3 topLeft, Vec3 topRight, Vec3 botLeft, Vec3 botRight) {
	_localRect[0] = topLeft;
	_localRect[1] = topRight;
	_localRect[2] = botLeft;
	_localRect[3] = botRight;
}
const bool BoxBounds::CheckInside(Vec3 pos)const {
	return (pos.x >= _worldRect[0].x && pos.x <= _worldRect[1].x &&
		pos.y >= _worldRect[3].y && pos.y <= _worldRect[0].y);
}
const float BoxBounds::GetZ() const{
	return _worldRect[0].z;
}
/*
todo I DONT THINK THIS NEEDS TO BE VIRTUAL
*/
void BoxBounds::Translate2World(const Matrix4x4* model)  {
	const int a = 0;
	int b = a;
	for (int i = 0; i < 4; ++i) {
		_worldRect[i] = (*model )* _localRect[i] ;
	}
}
