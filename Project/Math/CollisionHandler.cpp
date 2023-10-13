#include "CollisionHandler.h"
#include "CollisionDetection.h"
#include "PhysicsObject.h"



std::vector< std::pair<Bounds*, BaseNode*>>*  CollisionHandler::_all_bounds = new std::vector< std::pair<Bounds*, BaseNode*>>();




void CollisionHandler::RegisterBounds( Bounds* b, BaseNode* bn) {
	_all_bounds->push_back(std::pair<Bounds*, BaseNode*>(b,bn));
}
/// <summary>
/// TO DO: COLLISION LAYERS
/// </summary>
/// <param name="deltaTime"></param>
void CollisionHandler::Update(const float deltaTime) {	
	if (_all_bounds->size() == 0) return;

	//check every bounds against every other bounds		
	for (int i = 0; i < _all_bounds->size()-1; ++i) {		
		
		Bounds* a = _all_bounds->at(i).first;			

		for (int j = i + 1; j < _all_bounds->size(); ++j) {	

			Bounds* b = _all_bounds->at(j).first;		

			const unsigned int collisionExists = a->IsColliding(b);
			if (a == b)									
				continue;								
			
			SeparationData sd = CollisionDetection::CheckCollision(a, b);

			if (sd._penetrationDistance !=0 ) {			
				//collision has happened				
				//no collision with this object happened last frame
				if (collisionExists == -1) {			
					if (a->_solid && b->_solid) {
						a->AddActiveCollision(b, sd);
						b->AddActiveCollision(a, sd);
					}
				}
				CollisionSeparation(_all_bounds->at(i), _all_bounds->at(j), sd);

			}
			else  if(sd._penetrationDistance == 0 && collisionExists != -1){
				//check if you have been colliding with b previously but have not yet called OnExitCollision
				if (collisionExists != -1) {
					//printf("EXITING COLLISION\n");
					a->RemoveActiveCollision(b);
				}
			}
		}
	}
}
//#define float/(Vec3 v){}
//Vec3 float::operator/(Vec3 v) {}
#include "../Util/Utility.h"
/// <summary>
/// this does not work and i dont know why. Doesnt look like it does in the tutorial video but that could be becausee of the camera zoom.
/// I have 1 being 1 pixel he has 1 being 1 object. The scale difference is why it doesnt bounce or look remotely how it should.
/// Potential solution being to write my own JANK somehow.
/// Something like energy or momentum transfer, when 2 objects collide type of shit.
/// REACCTION FORCES.
/// Maybe you should finish watching the entire set of tutorials, maybe it gets addressed somewhere.
/// </summary>
/// <param name="a"></param>
/// <param name="b"></param>
/// <param name="sd"></param>
void CollisionHandler::CollisionSeparation(std::pair<Bounds*, BaseNode*>& a, std::pair<Bounds*, BaseNode*>& b, SeparationData& sd) {
	
	PhysicsObject* bodyA = a.second->GetComponent<PhysicsObject>();
	PhysicsObject* bodyB = b.second->GetComponent<PhysicsObject>();
	

	//								seperate objects apart from each other
	//Transform bt = b.second->GetTransform();
	//b.second->SetPosition(bt._position + sd._separationVector * (sd._penetrationDistance * 0.6f));

	Transform at = a.second->GetTransform();
	a.second->SetPosition(at._position + sd._separationVector * (sd._penetrationDistance * -1.0f));

	//								physics response
	if (bodyA == NULL || bodyB == NULL) {
		printf("THERES A PROBLEM A BODY WAS NULL\n");
		return;
	}
	Vec3 relativeVelocity = (*bodyB->GetVelocity()) - (*bodyA->GetVelocity());		
	float e = std::min(bodyA->GetCoefRestitution(), bodyB->GetCoefRestitution());	
	float j = -(1.0f + e) * Vec3::Dot(relativeVelocity, sd._separationVector);		
	j /= (1.0f / bodyA->GetMass()) + (1.0f / bodyB->GetMass());						
	Vec3* velA = bodyA->GetVelocity();
	Vec3* velB = bodyB->GetVelocity();
	//(*bodyA->GetVelocity()) += j / ( bodyA->GetMass() * sd._separationVector);
	(*velA ) -= (j / bodyA->GetMass()) * sd._separationVector;
	//(*bodyB->GetVelocity()) -= j / (bodyB->GetMass() * sd._separationVector) ;
	(*velB) += (j / bodyB->GetMass()) * sd._separationVector;
}


bool CollisionHandler::RayCast(Ray* ray, RayHitData& hitData) {

	//find every plane
	//check plane intersection
	//use DOT product to check if intersection is within polygonal bounds of the plane
	for (int i = 0; i < _all_bounds->size(); i++) {
		auto pair = _all_bounds->at(i);
		Bounds* b = pair.first;
		if (b->_type != BoundsType::BB)
			continue;

		auto s = b->GetShape();

		

	}
	return false;
	
}



void CollisionHandler::Delete() {
	delete _all_bounds;
}


/*
	spacial hashing 
	collsision between different shape types


*/