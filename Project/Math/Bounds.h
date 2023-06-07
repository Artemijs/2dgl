#ifndef BOUNDS_H
#define BOUNDS_H

#define shape std::pair<const unsigned int,  Vec3*>

#include "Matrix4x4.h"
#include "../Game/BaseComponent.h"
/// <summary>
/// total of 4 types, used to call different collision detection calls based on type
/// </summary>
enum class BoundsType{
	AABB = 0,
	BB,
	CIRCLE,
	TRIANGLE,
};


class Bounds: public BaseComponent {
public:
	static const unsigned int _component_id;
	Vec3 _centerOfMass;
	const BoundsType _type;
	Bounds(BoundsType bt);
	//BaseComponent* comp;
	//virtual const bool CheckInside(const Vec3 pos)const  = 0;
	virtual void Translate2World(const Matrix4x4* model)  = 0;
	const unsigned int ID() const override;
	virtual const  shape GetShape() const  = 0 ;
	const Vec3* GetCenterOfMass();
};
#endif // !BOUNDS_H
