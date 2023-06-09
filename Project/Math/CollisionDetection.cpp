#include "CollisionDetection.h"
#include <functional>
#include "../Util/Utility.h"






SeparationData CollisionDetection::CheckAABB(const Bounds* a, const Bounds* b) {
	SeparationData sd;
	if (b->_type == BoundsType::AABB) {
		return CheckAABBCollision(a->GetShape(), b->GetShape());
	}
	else if (b->_type == BoundsType::BB) {
		SAT(a->GetShape(), b->GetShape());
		return sd;//
	}
	else if (b->_type == BoundsType::CIRCLE) {
		auto bs = b->GetShape();
		//bs.second[1].x is where the radius is stored of the circle FEEL FREE TO CLEAN THIS UP
		//this gets the second point to create the axis with
		//CAN BE OPTIMISED TO USE THE NORMALISED DIRECTION AS AXIS 
		bs.second[1] = Vec3::Normalize(b->_centerOfMass - a->_centerOfMass)* bs.second[1].x;
		SAT(a->GetShape(), bs);
		return sd;
	}
	else if (b->_type == BoundsType::TRIANGLE) {
		std::cout << " TRAINGLES NOT REALLY SUPPORTED\n";
		return sd;
	}
}
SeparationData CollisionDetection::CheckCircle(const Bounds* a, const Bounds* b) {
	SeparationData sd;
	auto as = b->GetShape();
	//bs.second[1].x is where the radius is stored of the circle FEEL FREE TO CLEAN THIS UP
	//this gets the second point to create the axis with
	//CAN BE OPTIMISED TO USE THE NORMALISED DIRECTION AS AXIS 
	as.second[1] = Vec3::Normalize(b->_centerOfMass - a->_centerOfMass) * as.second[1].x;
	if (b->_type == BoundsType::AABB) {
		SAT(as, b->GetShape());
		return sd;
	}
	else if (b->_type == BoundsType::BB) {
		SAT(as, b->GetShape());
		return sd;//
	}
	else if (b->_type == BoundsType::CIRCLE) {
		//COllisionDetection Circle Circle
		return CircleCircleCollision(a->GetShape(), b->GetShape());
	}
	else if (b->_type == BoundsType::TRIANGLE) {
		std::cout << " TRAINGLES NOT REALLY SUPPORTED\n";
		return sd;
	}

}
SeparationData CollisionDetection::CheckBB(const Bounds* a, const Bounds* b) {
	SeparationData sd;
	if (b->_type == BoundsType::AABB) {
		return CheckAABBCollision(a->GetShape(), b->GetShape());
	}
	else if (b->_type == BoundsType::BB) {
		SAT(a->GetShape(), b->GetShape());
		return sd;//
	}
	else if (b->_type == BoundsType::CIRCLE) {
		auto bs = b->GetShape();
		//bs.second[1].x is where the radius is stored of the circle FEEL FREE TO CLEAN THIS UP
		//this gets the second point to create the axis with
		//CAN BE OPTIMISED TO USE THE NORMALISED DIRECTION AS AXIS 
		bs.second[1] = Vec3::Normalize(b->_centerOfMass - a->_centerOfMass) * bs.second[1].x;
		SAT(a->GetShape(), bs);
		return sd;
	}
	else if (b->_type == BoundsType::TRIANGLE) {
		std::cout << " TRAINGLES NOT REALLY SUPPORTED\n";
		return sd;
	}

}


SeparationData CollisionDetection::CheckCollision(const Bounds* a, const Bounds* b) {
	//the idea here is that i will call a function in an array based on type using 
	
	/*if (a->_type == BoundsType::AABB) {
		return CheckAABB(a, b);
	}
	else if (a->_type == BoundsType::BB) {
		return CheckBB(a, b);
	}
	else if (a->_type == BoundsType::CIRCLE) {
		return CheckCircle(a, b);
	}
	else {
		
	}*/

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




SeparationData CollisionDetection::CheckCollision(const shape& a, const shape &b, const float aRad , const float bRad) {
	
	SeparationData s; 
	if (a.first == 1 ) {//point
		if (b.first == 1) {
			return s;// a.second == b.second;
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
			return s;//a.second == b.second;
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
			return s; //a.second == b.second;
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
			return s;// a.second == b.second;
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
	return s;

}




bool CollisionDetection::_print = false;

/// <summary>
/// Check if a point is inside a bounds using separatin axis theorum
/// </summary>
/// <param name="p"> vec3 point </param>
/// <param name="s"> pair of int array len, vec3* array start</param>
/// <returns></returns>
const float CollisionDetection::CheckPointSAT(const Vec3& p, const shape& s) {
	
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
			_print = false;
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
	SeparationData sd;
	bool finished = false;
	//NEED TO FIND AXIS AV1 - AV2, AV2 - AV3, AV4 - AV1, BV1 - BV2, BBV2- BV3, BV3 - BV4, BV4 - BV1
	int i = 0;
	unsigned int index;
	const Vec3 *p1, *p2;
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
	return sd;
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