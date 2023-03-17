#ifndef BOUNDS_H
#define BOUNDS_H
#include "Matrix4x4.h"
class Bounds {
public :
	virtual bool CheckInside(Vec3 pos) = 0;
	virtual float GetZ() = 0;
};
#endif // !BOUNDS_H
