#ifndef BOUNDS_H
#define BOUNDS_H

#define shape std::pair<const unsigned int, const Vec3*>

#include "Matrix4x4.h"
#include "../Game/BaseComponent.h"
class Bounds: public BaseComponent {
public:
	static const unsigned int _component_id;
	//Bounds():BaseComponent() {}
	//BaseComponent* comp;
	virtual const bool CheckInside(const Vec3 pos)const  = 0;
	virtual void Translate2World(const Matrix4x4* model)  = 0;
	const unsigned int ID() const override;
	virtual const  shape GetShape() const  = 0 ;
};
#endif // !BOUNDS_H
