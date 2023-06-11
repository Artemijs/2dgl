#include "CollisionHandler.h"
#include "CollisionDetection.h"
std::vector< Bounds*>*  CollisionHandler::_all_bounds = new std::vector< Bounds*>();

void CollisionHandler::RegisterBounds( Bounds* b) {
	_all_bounds->push_back(b);
}
/// <summary>
/// TO DO: COLLISION LAYERS
/// </summary>
/// <param name="deltaTime"></param>
void CollisionHandler::Update(const float deltaTime) {
	//check every bounds against every other bounds
	for (int i = 0; i < _all_bounds->size(); ++i) {
		  Bounds* a = _all_bounds->at(i);
		for (int j = 0; j < _all_bounds->size(); ++j) {
			  Bounds* b = _all_bounds->at(j);
			if (a == b)
				continue;
			
			SeparationData sd = CollisionDetection::CheckCollision(a, b);
			if (sd._penetrationDistance !=0) {
				if (a->_solid && b->_solid) {
					CollisionSeparation(a, b, sd);
				}
				
				//call any oncollision events
			}
			
		}
	}
}

void CollisionHandler::CollisionSeparation(const Bounds* a, const Bounds* b, SeparationData& sd) {
	printf("COLLIDEDD\n");
}

void CollisionHandler::Delete() {
	delete _all_bounds;
}


/*
	spacial hashing 
	collsision between different shape types


*/