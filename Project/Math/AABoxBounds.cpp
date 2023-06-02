#include "AABoxBounds.h"
AABoxBounds::AABoxBounds() {

	_localRect[0] = Vec3(-0.5f, 0.5f, 0.1f);
	_localRect[1] = Vec3(0.5f, 0.5f, 0.1f);
	_localRect[2] = Vec3(-0.5f, -0.5f, 0.1f);
	_localRect[3] = Vec3(0.5f, -0.5f, 0.1f);
}
AABoxBounds::AABoxBounds(const Vec3 topLeft, const Vec3 topRight, const Vec3 botLeft, const Vec3 botRight) {
	_localRect[0] = topLeft;
	_localRect[1] = topRight;
	_localRect[2] = botLeft;
	_localRect[3] = botRight;
}
const bool AABoxBounds::CheckInside(const Vec3 pos)const {
	return (pos.x >= _worldRect[0].x && pos.x <= _worldRect[1].x &&
		pos.y >= _worldRect[3].y && pos.y <= _worldRect[0].y);
}

void AABoxBounds::Translate2World(const Matrix4x4* model)  {
	for (int i = 0; i < 4; ++i) {
		_worldRect[i] = (*model )* _localRect[i] ;
	}
}

const shape AABoxBounds::GetShape() const {
	return shape(4, _worldRect);
}
