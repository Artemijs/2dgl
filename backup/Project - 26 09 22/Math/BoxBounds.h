#ifndef BOX_BOUNDS_H
#define BOX_BOUNDS_H
#include "Bounds.h"
class BoxBounds : public Bounds{
private:
	Vec3 _topLeft, _topRight, _botLeft, _botRight;
public :
	BoxBounds(Vec3 topLeft, Vec3 topRight, Vec3 botLeft, Vec3 botRight);
	bool CheckInside(Vec3 pos);
	float GetZ();
};
#endif