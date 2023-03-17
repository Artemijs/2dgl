#include "BoxBounds.h"

BoxBounds::BoxBounds(Vec3 topLeft, Vec3 topRight, Vec3 botLeft, Vec3 botRight):
	_topLeft(topLeft), _topRight(topRight), _botRight(botRight), _botLeft(botLeft) {
}
bool BoxBounds::CheckInside(Vec3 pos) {
	return (pos.x >= _topLeft.x && pos.x <= _topRight.x &&
		pos.y >= _botLeft.y && pos.y <= _topLeft.y);
}
float BoxBounds::GetZ() {
	return _topLeft.z;
}