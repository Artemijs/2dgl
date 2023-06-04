#include "CollisionHandler.h"

std::vector<const Bounds*>*  CollisionHandler::_all_bounds = new std::vector<const Bounds*>();

void CollisionHandler::RegisterBounds(const Bounds* b) {
	_all_bounds->push_back(b);
}

void CollisionHandler::Update(const float deltaTime) {
	//
}

void CollisionHandler::Delete() {
	delete _all_bounds;
}


/*
	spacial hashing 
	collsision between different shape types


*/