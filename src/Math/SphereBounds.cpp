#include "Math/SphereBounds.h"
SphereBounds::SphereBounds(BaseNode* owner):
	_localPosition(Vec3()),
	_radius(50),
	Bounds(BoundsType::CIRCLE, owner)
{
	_worldPosition[0] =  owner->GetTransform()._position;
	_worldPosition[1] = Vec3();

	
}
/// <summary>
/// 
/// </summary>
/// <param name="rad">size of circle</param>
/// <param name="pos">LOCAL SPACE OFFSET deffault to 0 for circles</param>
SphereBounds::SphereBounds(BaseNode* owner, const float rad, const Vec3 pos):
	_radius(rad),
	_localPosition(pos),
	Bounds(BoundsType::CIRCLE, owner)
{
	_worldPosition[0] = owner->GetTransform()._position;
	_worldPosition[1] = Vec3();
}
//const bool SphereBounds::CheckInside(Vec3 pos)const {
	//distance formula is needed 
	//return (Vec3::Distance(_worldPosition, pos) <= _radius);
//}

//todo I DONT THINK THIS NEEDS TO BE VIRTUAL

void SphereBounds::Translate2World(const Matrix4x4* model)  {
	_worldPosition[0] = model->GetPosition();
	_centerOfMass = model->GetPosition();
	_worldPosition[1] = Vec3(_radius, _radius, _radius);
}
shape SphereBounds::GetShape()   {
	 
	return shape(2, _worldPosition);//_worldRect;
}
/// <summary>
/// returns the pointer to the radius
/// </summary>
/// <returns></returns>
float* SphereBounds::GetSize() {
	return &_radius;
}