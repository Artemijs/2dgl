/*#ifndef SPHERE_BOUNDS_H
#define SPHERE_BOUNDS_H
#include "Bounds.h"
class SphereBounds : public Bounds{
private:
	//the second position is used in the collision algorythm
	Vec3  _localPosition;
	Vec3  _worldPosition[2];
	float _radius;		
public :
	SphereBounds();
	SphereBounds( const float _radius, const Vec3 pos = Vec3());
	//const bool CheckInside(const Vec3 pos)const ;
	void Translate2World(const Matrix4x4* model) ;
	const shape GetShape() const override;
};
#endif
*/