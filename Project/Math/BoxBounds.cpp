#include "BoxBounds.h"
#include "CollisionDetection.h"
BoxBounds::BoxBounds():Bounds(BoundsType::BB) {

	_localRect[0] = Vec3(-0.5f, 0.5f, 0.1f);//top left 
	_localRect[1] = Vec3(0.5f, 0.5f, 0.1f);//top right
	_localRect[2] = Vec3(0.5f, -0.5f, 0.1f);// bot right
	_localRect[3] = Vec3(-0.5f, -0.5f, 0.1f);//bot left
}
BoxBounds::BoxBounds(const Vec3 topLeft, const Vec3 topRight, const Vec3 botLeft, const Vec3 botRight) :
	Bounds(BoundsType::BB) {
	_localRect[0] = topLeft;	
	_localRect[1] = topRight;	
	_localRect[2] = botLeft;	
	_localRect[3] = botRight;	
}


/*
todo I DONT THINK THIS NEEDS TO BE VIRTUAL
*/
void BoxBounds::Translate2World(const Matrix4x4* model)  {
	const int a = 0;
	int b = a;
	for (int i = 0; i < 4; ++i) {
		_worldRect[i] = (*model )* _localRect[i] ;
	}
	_centerOfMass = (*model) * _centerOfMass;
}
 const shape BoxBounds::GetShape() const {
	return   shape(4, _worldRect);
}