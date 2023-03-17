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
bool BoxBounds::CheckInside(Vec3 pos) {
	return (pos.x >= _worldRect[0].x && pos.x <= _worldRect[1].x &&
		pos.y >= _worldRect[3].y && pos.y <= _worldRect[0].y);
}
float BoxBounds::GetZ() {
	return _worldRect[0].z;
}
void BoxBounds::Translate2World(Matrix4x4 model) {
	for (int i = 0; i < 4; ++i) {
		_worldRect[i] = model * _localRect[i] ;
	}
}
