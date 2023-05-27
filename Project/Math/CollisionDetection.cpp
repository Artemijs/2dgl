#include "CollisionDetection.h"
#include <functional>


//I THINK I NEED TO UPDATE SHAPE NORMAL VECTORS AS I UPDATE MODEL MATRIX

const bool CollisionDetection::SAT(shape a, shape b) {
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
		
		
		

		//IF THE PENETRATION IS TOO DEEP THE OBJECTS WILL EXPLODE IN RANDOM DIRECTIONS
		std::function<float(float, float, float, float)> checkOverlap = [&](float minA, float maxA, float minB, float maxB) {
			float penDist = 0.0f;
			//any point in a is inside of b OR any point in b is inside of a
			/*if (minA >= minB && minA <= maxB ||
				maxA >= minB && maxA <= maxB ||
				minB >= minA && minB <= maxA ||
				maxB >= minA && maxB <= maxA) {


			}*/
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
		};

		std::function< Vec2(Vec3, Vec3)> getAxis = [&](Vec3 p1, Vec3 p2) {
			//direction from a to b
			Vec2 dir2p2 = Vec2(p2.x - p1.x, p2.y - p1.y);
			dir2p2.Normalize();
			//get the normal vector that will be used as the axis for translation
			float x = dir2p2.x;
			dir2p2.x = -dir2p2.y;
			dir2p2.y = x;
			return  dir2p2;
		};

		Vec2 axis = getAxis((*p1), (*p2));

		std::function<void(float, float, shape)> projectOnAxis =
			[&, axis](float min, float max, shape s) {

			auto points = s.second;

			for (int i = 0; i < s.first; ++i) {
				float d = Vec2::Dot(points[i].x, points[i].y, axis.x, axis.y);
				if (d < min)
					min = d;
				if (d > max)
					max = d;
			}
		};

		float minA = 10000000000;
		float maxA = -11111111111;
		float minB = 10000000000;
		float maxB = -11111111111;
		projectOnAxis(minA, maxA, a);
		projectOnAxis(minB, maxB, b);

		float penetrationDistance = checkOverlap(minA, maxA, minB, maxB);
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

