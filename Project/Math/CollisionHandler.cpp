#include "CollisionHandler.h"
#include "CollisionDetection.h"
std::vector<const Bounds*>*  CollisionHandler::_all_bounds = new std::vector<const Bounds*>();

void CollisionHandler::RegisterBounds(const Bounds* b) {
	_all_bounds->push_back(b);
}

void CollisionHandler::Update(const float deltaTime) {
	//check every bounds against every other bounds
	for (int i = 0; i < _all_bounds->size(); ++i) {
		const Bounds* a = _all_bounds->at(i);
		for (int j = 0; j < _all_bounds->size(); ++j) {
			const Bounds* b = _all_bounds->at(j);
			if (a == b)
				continue;
			CollisionDetection::CheckCollision(a, b);
		}
	}
}
void CollisionHandler::CollisionSeparation(const Bounds* a, const Bounds* b, SeparationData& sd) {
	
}
void CollisionHandler::Delete() {
	delete _all_bounds;
}


/*
	spacial hashing 
	collsision between different shape types


*/