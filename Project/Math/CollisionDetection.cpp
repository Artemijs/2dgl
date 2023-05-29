#include "CollisionDetection.h"
#include <functional>













const bool CollisionDetection::CheckCollision(const shape& a, const shape &b) {
	if (a.first == 1 ) {//point
		if (b.first == 1) {
			return a.second == b.second;
		}
		else if (b.first == 2) {
			//radius and position
			// circle
		}
		else if (b.first == 3) {
			//triangle
		}
		else if (b.first == 4) {
			//square		
		}
		else {
			//other shapes
		}
	}
	else if (a.first == 2) {//circle
		if (b.first == 1) {
			//point
		}
		else if (b.first == 2) {
			// circle
		}
		else if (b.first == 3) {
			//triangle
		}
		else if (b.first == 4) {
			//square		
		}
		else {
			//other shapes
		}
	}
	else if (a.first == 3) {//triangle
		if (b.first == 1) {
			return a.second == b.second;
		}
		else if (b.first == 2) {
			//point circle
		}
		else if (b.first == 3) {
			//triangle
		}
		else if (b.first == 4) {
			//square		
		}
		else {
			//other shapes
		}
	}
	else if (a.first == 4) {//square
		if (b.first == 1) {
			return a.second == b.second;
		}
		else if (b.first == 2) {
			//point circle
		}
		else if (b.first == 3) {
			//triangle
		}
		else if (b.first == 4) {
			//square		
		}
		else {
			//other shapes
		}
	}
	else {
		if (b.first == 1) {
			return a.second == b.second;
		}
		else if (b.first == 2) {
			//point circle
		}
		else if (b.first == 3) {
			//triangle
		}
		else if (b.first == 4) {
			//square		
		}
		else {
			//other shapes
		}
	}


}

















//I THINK I NEED TO UPDATE SHAPE NORMAL VECTORS AS I UPDATE MODEL MATRIX

const bool CollisionDetection::SAT(const shape a, const shape b) {
	bool finished = false;
	//NEED TO FIND AXIS AV1 - AV2, AV2 - AV3, AV4 - AV1, BV1 - BV2, BBV2- BV3, BV3 - BV4, BV4 - BV1
	int i = 0;
	unsigned int index;
	Vec3 *p1, *p2;
	float smalestPenetration = 100000000000;
	bool collisionDetected = true;
	while (!finished) {
		
		if (i < a.first) {
			//THIS NEEDS TO BE OPTIMISED TO NOT REUSE AXIS
			p1 = &a.second[i];
			p2 = &a.second[i+1];
		}
		else {
			p1 = &b.second[i - a.first];
			p2 = &b.second[i + 1 - a.first];
			if (i + 1 >= a.first + b.first) {
				finished = true;
			}
		}
		
		Vec2 axis = GetAxis((*p1), (*p2));

		float minA = 10000000000;
		float maxA = -11111111111;
		float minB = 10000000000;
		float maxB = -11111111111;
		ProjectOnAxis(minA, maxA, axis, a);
		ProjectOnAxis(minB, maxB, axis, b);

		float penetrationDistance = CheckOverlap(minA, maxA, minB, maxB);
		//find the smallest penetration distance
		if (penetrationDistance == 0) {
			// no penetration at all
			finished = true;
			collisionDetected = false;
			break;
		}
		else {
			if (penetrationDistance < smalestPenetration) {
				smalestPenetration = penetrationDistance;
			}
		}
		i++;
	}
	return collisionDetected;
}
//IF THE PENETRATION IS TOO DEEP THE OBJECTS WILL EXPLODE IN RANDOM DIRECTIONS
const float CollisionDetection::CheckOverlap(const float minA, const float maxA, const float minB, const float maxB) {
	float penDist = 0.0f;
	//if  the right side of b collides with the left side of a
	if (maxB > minA && maxB < maxA) {
		penDist = maxB - minA;
	}
	//if the left side of b collidees with the irhgt side of a
	else if (minB < maxA && minB > minA) {
		penDist = maxA - minB;
	}
	//I ALSO AM IN GREATEST OF NEEDS FOR THE SMALLEST PENETRATION DISTANCE OF ALL THE PENETRATIONS ON EVERY AXIS
	return penDist;
}
const Vec2 CollisionDetection::GetAxis(const Vec3& p1, const Vec3& p2) {
	//direction from a to b
	Vec2 dir2p2 = Vec2(p2.x - p1.x, p2.y - p1.y);
	dir2p2.Normalize();
	//get the normal vector that will be used as the axis for translation
	float x = dir2p2.x;
	dir2p2.x = -dir2p2.y;
	dir2p2.y = x;
	return  dir2p2;
}
const void CollisionDetection::ProjectOnAxis(float& min, float& max, const Vec2 axis, const shape& s) {
	auto points = s.second;

	for (int i = 0; i < s.first; ++i) {
		float d = Vec2::Dot(points[i].x, points[i].y, axis.x, axis.y);
		if (d < min)
			min = d;
		if (d > max)
			max = d;
	}
}

