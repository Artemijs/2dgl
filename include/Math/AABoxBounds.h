/*#ifndef AABOX_BOUNDS_H
#define AABOX_BOUNDS_H
#include "BoxBounds.h"



class AABoxBounds : public BoxBounds {
private:
	//0 : top left, 1 : top right, 2 : bot left, 3: botright
	Vec3 _localRect[4];
	Vec3 _worldRect[4];
	float _size[2];

public :
	AABoxBounds(BaseNode* owner);
	AABoxBounds(BaseNode* owner, const Vec3 topLeft, const Vec3 topRight, const Vec3 botLeft, const Vec3 botRight);

};

#endif

*/