#ifndef BOUNDS_H
#define BOUNDS_H
#include "Matrix4x4.h"
//#include "../Game/BaseComponent.h"
class Bounds {
	
public :
	//BaseComponent* comp;
	virtual bool CheckInside(Vec3 pos) = 0;
	virtual float GetZ() = 0;
	virtual void Translate2World(Matrix4x4 model) = 0;
};
#endif // !BOUNDS_H
