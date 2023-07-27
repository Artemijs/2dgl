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
			  const unsigned int collisionExists = a->IsColliding(b);
			if (a == b)
				continue;
			SeparationData sd = CollisionDetection::CheckCollision(a, b);
			if (sd._penetrationDistance !=0 && collisionExists == -1) {
				//collision has happened and no collision with this object happened last frame
				if (a->_solid && b->_solid) {
					a->AddActiveCollision(b, sd);
					b->AddActiveCollision(a, sd);
					CollisionSeparation(a, b, sd);
				}
			}
			else  if(sd._penetrationDistance == 0 && collisionExists != -1){
				//check if you have been colliding with b previously but have not yet called OnExitCollision
				if (collisionExists != -1) {
					printf("EXITING COLLISION\n");
					a->RemoveActiveCollision(b);
				}
				//check if a was colliding with b
				//const unsigned int collision_index = isColliding(b);
				//if(collision_index !=-1)
				//	a->EndCollision(b);
			}
		}
	}
}

void CollisionHandler::CollisionSeparation(const Bounds* a, const Bounds* b, SeparationData& sd) {
	printf("COLLIDEDD\n");
	//check if the object cannot be moved
	//if both objects can be moved then part them equally and separate directions
	//if only one object can be moved part that one object fully

}

void CollisionHandler::CallEvents(Bounds* a, Bounds* b, const SeparationData* sd) {
	if (sd->_penetrationDistance > 0) {//colllision true
		//a->OnCollisionEnter();
	}
	else {//collision false
	
	}
}



void CollisionHandler::Delete() {
	delete _all_bounds;
}


/*
	spacial hashing 
	collsision between different shape types


*/