#ifndef BOUNDS_H
#define BOUNDS_H
#include "Matrix4x4.h"
#include "../Game/BaseComponent.h"
class Bounds: public BaseComponent {
public:
	static const unsigned int _id;
	//Bounds():BaseComponent() {}
	//BaseComponent* comp;
	virtual const bool CheckInside(const Vec3 pos)const  = 0;
	virtual const float GetZ()const = 0;
	virtual void Translate2World(const Matrix4x4* model)  = 0;
	const unsigned int ID() const override;
};
#endif // !BOUNDS_H
