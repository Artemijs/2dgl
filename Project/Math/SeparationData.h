#ifndef SEPARATIONDATA_H
#define SEPARATIONDATA_H
#include "Matrix4x4.h"
struct SeparationData {
public:
	float _penetrationDistance;
	Vec3 _separationVector;
};

#endif