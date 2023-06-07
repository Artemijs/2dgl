#include "SphereBounds.h"
SphereBounds::SphereBounds():
	_localPosition(Vec3()),
	_radius(50),
	Bounds(BoundsType::CIRCLE)
{
	_worldPosition[0] = Vec3();
	_worldPosition[1] = Vec3(_radius, _radius, _radius);
	
}
/// <summary>
/// 
/// </summary>
/// <param name="rad">size of circle</param>
/// <param name="pos">position is local space</param>
SphereBounds::SphereBounds(const float rad, const Vec3 pos):
	_radius(rad),
	_localPosition(pos),
	Bounds(BoundsType::CIRCLE)
{
	_worldPosition[0] = pos;
	_worldPosition[1] = Vec3(_radius, _radius, _radius);
}
/*const bool SphereBounds::CheckInside(Vec3 pos)const {
	//distance formula is needed 
	return (Vec3::Distance(_worldPosition, pos) <= _radius);
}*/
/*
todo I DONT THINK THIS NEEDS TO BE VIRTUAL
*/
void SphereBounds::Translate2World(const Matrix4x4* model)  {
	_worldPosition[0] = (*model) * _localPosition;
	_centerOfMass = (*model) * _centerOfMass;
	_worldPosition[1] = Vec3(_radius, _radius, _radius);
	
}
 const shape SphereBounds::GetShape() const  {
	 
	return shape(2, _worldPosition);//_worldRect;
}