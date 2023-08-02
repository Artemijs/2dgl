#include "CollisionDetection.h"
#include <functional>
#include "../Util/Utility.h"
//#include <math.h>

/// THINGS THAT CAN BE OPTIMISED 
/// passing SEPARATION DATA pointer instead of copying that data every function call
/// Point to AABB a nd POINT to Circle
/// 

bool CollisionDetection::_print = false;


SeparationData CollisionDetection::CheckCollision( Bounds* a,  Bounds* b) {
	//the idea here is that i will call a function in an array based on type using 
	
	if (a->_type == BoundsType::CIRCLE && b->_type == BoundsType::CIRCLE) {
		return CircleCircleCollision(a->GetShape(), b->GetShape());
	}
	else if(a->_type == BoundsType::AABB && b->_type == BoundsType::AABB) {
		return CheckAABBCollision(a->GetShape(), b->GetShape());
	}
	else {
		auto as = a->GetShape();
		auto bs = b->GetShape();
		if (a->_type == BoundsType::CIRCLE) {
			
			//bs.second[1].x is where the radius is stored of the circle FEEL FREE TO CLEAN THIS UP
			//this gets the second point to create the axis with
			//CAN BE OPTIMISED TO USE THE NORMALISED DIRECTION AS AXIS 
			as.second[1] = Vec3::Normalize(b->_centerOfMass - a->_centerOfMass) * as.second[1].x;
			//SAT(a->GetShape(), bs);
		}
		if ( b->_type == BoundsType::CIRCLE) {
			//bs.second[1].x is where the radius is stored of the circle FEEL FREE TO CLEAN THIS UP
			//this gets the second point to create the axis with
			//CAN BE OPTIMISED TO USE THE NORMALISED DIRECTION AS AXIS 
			bs.second[1] = Vec3::Normalize(b->_centerOfMass - a->_centerOfMass) * bs.second[1].x;
		}
		return SAT(as, bs);

	}


}

/// <summary>
/// Check if a point is inside a bounds using separatin axis theorum
/// </summary>
/// <param name="p"> vec3 point </param>
/// <param name="s"> pair of int array len, vec3* array start</param>
/// <returns></returns>
const float CollisionDetection::CheckPointSAT(const Vec3& p, const shape& s) {
	if(_print)
		printf("\nchecking point sat\n");
	const Vec3* p1, *p2;
	float smalestPenetration = 100000000000;
	if (_print) {
		std::cout << "\n";
		for (int i = 0; i < s.first; i++) {
			//std::cout << "v" << i << " : " << "(" << s.second[i].x << " ," << s.second[i].y << " ," << s.second[i].z << ")\n";
			std::cout << "v" << i;
			Utility::PrintVector(" : ", s.second[i]);
		}
		Utility::PrintVector(" point : ", p);
		std::cout << "\n";
	
	}
	for( int i = 0; i < s.first-1; ++i) {
		if(_print)
			std::cout << "\n";
		p1 = &s.second[i];
		p2 = &s.second[i + 1];

		Vec2 axis = GetAxis((*p1), (*p2));
		
		if (_print) {
			Utility::PrintVector("v1 : ", (*p1)); 
			Utility::PrintVector("v2 : ", (*p2)); 
			Utility::PrintVector("axis : ", axis);
		
		}
		
		float minA = 10000000000;
		float maxA = -11111111111;
		
		ProjectOnAxis(minA, maxA, axis, s);
		float pDot = Vec2::Dot(p.x, p.y, axis.x, axis.y);
		if (_print) {
			std::cout << " projections :			a " << minA << " b " << maxA << " point " << pDot << "\n";
		}

		float penetrationDistance = 0;
		
		pDot += 1000000;
		minA += 1000000;
		maxA += 1000000;
		if (pDot > minA && pDot < maxA) {
			penetrationDistance = Utility::Dist2CLosest(minA, maxA, pDot);

			if (penetrationDistance < smalestPenetration) {
				smalestPenetration = penetrationDistance;
			}
			if (_print) {
				std::cout << "PENETRATION	:	" << penetrationDistance<<"\n";
				std::cout << "SMALLEST PENETRATION	:	" << smalestPenetration<<"\n";
			}
		}
		else {
			if(_print)
				std::cout << "NO OVERLAP DETECTED \n";
			//_print = false;
			return 0;
		}
		
	}
	if (_print)
	{
		_print = false;
	}
	return smalestPenetration;
}










//I THINK I NEED TO UPDATE SHAPE NORMAL VECTORS AS I UPDATE MODEL MATRIX

const SeparationData CollisionDetection::SAT(const shape a, const shape b) {
	if (_print)
		printf("\nSTARTING COLLISION SAT\n");
	SeparationData sd;
	sd._penetrationDistance = 10000000000;

	bool finished = false;
	int i = 0;
	Vec3 *p1 = NULL, *p2 = NULL;
	
	const shape* s = &a;
	while (!finished) {
		
		if (i < s->first-1) {
			//THIS NEEDS TO BE OPTIMISED TO NOT REUSE AXIS
			p1 = &s->second[i];
			p2 = &s->second[i + 1];

		}
		else {
			if (s != &b) {
				s = &b;
				i = 0;
			}
			else {
				finished = true;
			}

		}
		
		Vec2 axis = GetAxis((*p1), (*p2));
		if (_print) {
			printf("\nAXIS : x %.3f, y %.3f, \n", axis.x, axis.y);
		}
		float minA = 10000000000;
		float maxA = -11111111111;
		float minB = 10000000000;
		float maxB = -11111111111;
		if (_print) 
			printf("PROJECTING ON AXIS SHAPE A\n");
		ProjectOnAxis(minA, maxA, axis, a);
		if (_print)
			printf("PROJECTING ON AXIS SHAPE B\n");
		ProjectOnAxis(minB, maxB, axis, b);
		if (_print)
			printf("\nMinA : %.3f, MaxA : %.3f, MinB : %.3f, MaxB : %.3f\n" , minA ,maxA, minB, maxB);
		auto od = CheckOverlap(minA, maxA, minB, maxB);
		float penetrationDistance = od.first;
		if (_print) {
			printf("Penetration Distance : %f\n", penetrationDistance);
		}
		//find the smallest penetration distance
		if (penetrationDistance == 0) {
			// no penetration at all
			sd._penetrationDistance = 0;
			finished = true;
			break;
		}
		else {
			if (penetrationDistance < sd._penetrationDistance) {
				sd._penetrationDistance = penetrationDistance;  
				sd._separationVector = Vec3(axis.x, axis.y, 0) * od.second;
			}
		}
		i++;
	}
	
	if (sd._penetrationDistance != 0) {
		printf("penetration distance %.3f\n, separation vector x %.3f, y %.3f\n", sd._penetrationDistance, sd._separationVector.x, sd._separationVector.y);
	}
	if (_print)
		printf("\n ending SAT penDistance : %f \n", sd._penetrationDistance);
	return sd;
}
//IF THE PENETRATION IS TOO DEEP THE OBJECTS WILL EXPLODE IN RANDOM DIRECTIONS
const std::pair<float, int> CollisionDetection::CheckOverlap(const float x1, const float y1, const float x2, const float y2) {
	/*x1 += 100000000;
	x2 += 100000000;
	y1 += 100000000;
	y2 += 100000000;*/
	std::pair<float, int> overlapData(0, false);
	
	float centre1 = x1 + ((y1-x1) * 0.5f);
	float centre2 = x2 + ((y2-x2) * 0.5f);
	
	if (centre1 > centre2) {
		//object is to the right
		overlapData.second = -1;
		//check if objects are intersecting at all
		if (centre1 - centre2 > ((y1 - x1) * 0.5f) + ((y2 - x2) * 0.5f)) {
			//if distance from cnters is greater than the 2  half widths combined
			//not intersecting
			overlapData.first = 0;
		}
		else
			overlapData.first= y2 - x1;
	}
	else {
		//object is to the left
		overlapData.second = 1;
		//check if objects are intersecting at all
		if (centre2 - centre1 > ((y1 - x1) * 0.5f) + ((y2 - x2) * 0.5f)) {
			//if distance from cnters is greater than the 2  half widths combined
			//not intersecting
			overlapData.first = 0;
		}
		else
			overlapData.first = y1 - x2;
	}

	return overlapData;
}
const Vec2 CollisionDetection::GetAxis(const Vec3& p1, const Vec3& p2) {
	//direction from a to b
	Vec2 dir2p2 = Vec2( std::abs(p2.x - p1.x), std::abs(p2.y - p1.y));
	dir2p2.Normalize();
	//get the normal vector that will be used as the axis for translation
	float x = dir2p2.x;
	dir2p2.x = dir2p2.y;
	dir2p2.y = x;
	return  dir2p2;
}
const void CollisionDetection::ProjectOnAxis(float& min, float& max, const Vec2 axis, const shape& s) {
	auto points = s.second;

	for (int i = 0; i < s.first; ++i) {
		float d = Vec2::Dot(points[i].x, points[i].y, axis.x, axis.y);
		if (_print) {
			printf("position : x %.3f, y %.3f     projection : %.3f\n", points[i].x, points[i].y, d);
		}
		if (d < min)
			min = d;
		if (d > max)
			max = d;
	}
}



const SeparationData CollisionDetection::CheckAABBCollision(const shape& a, const shape& b) {
	SeparationData sd;
	for (int i = 0; i < a.first; ++i) {
		
		const Vec3* v1 = &a.second[i];
		if (v1->x > b.second[0].x && v1->x < b.second[1].x &&
			v1->y > b.second[0].y && v1->y < b.second[2].y) {
			return sd;
		}
	}
	for (int i = 0; i < b.first; ++i) {

		const Vec3* v1 = &b.second[i];
		if (v1->x > a.second[0].x && v1->x < a.second[1].x &&
			v1->y > a.second[0].y && v1->y < a.second[2].y) {
			return sd;
		}
	}
	return sd;
}
const SeparationData CollisionDetection::CircleCircleCollision(const shape& a, const shape& b) {
	//direction between one and the other 
	Vec3 dist = (b.second[0] - a.second[0]);
	const float distLen = dist.Lenght();
	const float totalCircleDist = (a.second[1].x + b.second[1].x);
	SeparationData sd;
	sd._penetrationDistance = totalCircleDist - distLen;
	dist.Normalize();
	sd._separationVector = dist;
	return sd;

}