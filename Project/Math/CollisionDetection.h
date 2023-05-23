#ifndef COLLISIONDETECTION_H
#define COLLISIONDETECTION_H
#include "Matrix4x4.h"
#include <utility>
#ifndef shape
#define shape std::pair<const unsigned int, Vec3*>
#endif

class CollisionDetection {
private:

public :
	static const bool SAT(shape a, shape b);
};
#endif

/*
bool SATCheck(point, box){

}
bool SATCheck(point, circle){

}
bool SATCheck(box, box){
		
}
bool SATCheck(box, circle){

}


bool SATCeck(pointsA, pointsB){
	for every point in pointsA and then pointsB
	{
		calculate axis

		dot product between axis and every point in points a
	
		get min and max of of dot product result to get the 1d shape
	
		dot product between axis and every point in points b

		get min and max of of dot product result to get the 1d shape

		check if the 2 overlap
	}

}
*/