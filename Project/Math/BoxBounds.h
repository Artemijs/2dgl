#ifndef BOX_BOUNDS_H
#define BOX_BOUNDS_H
#include "Bounds.h"

class BoxBounds : public Bounds{
private:
	//0 : top left, 1 : top right, 2 : bot left, 3: botright
	Vec3 _localRect[4];
	Vec3 _worldRect[4];
public :
	BoxBounds();
	BoxBounds(const Vec3 topLeft, const Vec3 topRight, const Vec3 botLeft, const Vec3 botRight);
	//const bool CheckInside(Vec3 pos) const;
	void Translate2World(const Matrix4x4* model);
	const shape GetShape() const override;
};
#endif