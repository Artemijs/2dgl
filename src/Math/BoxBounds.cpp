#include "Math/BoxBounds.h"
#include "Math/CollisionDetection.h"




BoxBounds::BoxBounds(BaseNode* owner):Bounds(BoundsType::BB, owner) {

	_localRect[0] = Vec3(-0.5f, 0.5f, 0.0f); //top left 
	_localRect[1] = Vec3(0.5f, 0.5f, 0.0f);  //top right
	_localRect[2] = Vec3(0.5f, -0.5f, 0.0f); //bot right
	_localRect[3] = Vec3(-0.5f, -0.5f, 0.0f);//bot left
	_centerOfMass = Vec3();
}


//use this to create an AABB
BoxBounds::BoxBounds(BaseNode* owner, BoundsType type) :Bounds(type, owner) {
	_localRect[0] = Vec3(-0.5f, 0.5f, 0.0f); //top left 
	_localRect[1] = Vec3(0.5f, 0.5f, 0.0f);  //top right
	_localRect[2] = Vec3(0.5f, -0.5f, 0.0f); //bot right
	_localRect[3] = Vec3(-0.5f, -0.5f, 0.0f);//bot left
	_centerOfMass = Vec3();
}


BoxBounds::BoxBounds(BaseNode* owner, const Vec3 topLeft, const Vec3 topRight, const Vec3 botLeft, const Vec3 botRight) :
	Bounds(BoundsType::BB, owner) {
	_localRect[0] = topLeft;	
	_localRect[1] = topRight;	
	_localRect[2] = botLeft;	
	_localRect[3] = botRight;	
	_centerOfMass = Vec3();
}

#include "Util/Utility.h"
/*
todo I DONT THINK THIS NEEDS TO BE VIRTUAL
*/
void BoxBounds::Translate2World(const Matrix4x4* model)  {
	const int a = 0;
	int b = a;
	for (int i = 0; i < 4; ++i) {
		_worldRect[i] = _offset * (*model ) * _localRect[i];
		//Utility::PrintVector("BoxBounds Positions : ", _worldRect[i]);
	}
	_centerOfMass = _offset * (*model) * Vec3(0, 0, 0);
}


shape BoxBounds::GetShape()  {
	// std::pair<const unsigned int, const Vec3*> p(four, &_worldRect[0]);
	// shape s(4, &_worldRect[0]);
	return  shape(4, _worldRect);
}


/// <summary>
/// returns an array _size
/// </summary>
/// <returns>_size[0] : width, _size[1] : height</returns>
float* BoxBounds::GetSize() {
	return _size;
}
