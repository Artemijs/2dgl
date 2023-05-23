#include "SphereBounds.h"
SphereBounds::SphereBounds():
	_localPosition(Vec3()),
	_worldPosition(Vec3()),
	_radius(50)
{

	
}
SphereBounds::SphereBounds(const float rad, const Vec3 pos):
	_radius(rad),
	_localPosition(pos),
	_worldPosition(Vec3())
{
	
}
const bool SphereBounds::CheckInside(Vec3 pos)const {
	//distance formula is needed 
	return (Vec3::Distance(_worldPosition, pos) <= _radius);
}
/*
todo I DONT THINK THIS NEEDS TO BE VIRTUAL
*/
void SphereBounds::Translate2World(const Matrix4x4* model)  {
	_worldPosition = (*model) * _localPosition;
	
}
shape SphereBounds::GetShape() {
	return shape(1, &_worldPosition);//_worldRect;
}