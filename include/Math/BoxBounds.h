#ifndef BOX_BOUNDS_H
#define BOX_BOUNDS_H
#include "Math/Bounds.h"




class BoxBounds : public Bounds{
private:
	//0 : top left, 1 : top right, 2 : bot left, 3: botright
	Vec3 _localRect[4];
	Vec3 _worldRect[4];
	float _size[2];
public :
	BoxBounds(BaseNode* owner);
	//special constructor that is used to create AABB
	BoxBounds(BaseNode* owner, BoundsType type);
	BoxBounds(BaseNode* owner, const Vec3 topLeft, const Vec3 topRight, const Vec3 botLeft, const Vec3 botRight);
	//const bool CheckInside(Vec3 pos) const;
	void Translate2World(const Matrix4x4* model);
	shape GetShape()  override;
	float* GetSize() override;
};
#endif