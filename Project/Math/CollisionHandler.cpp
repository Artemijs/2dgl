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
			
			SeparationData sd;
			CollisionDetection::CheckCollision(a, b, sd);

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
	bool physics = (bodyA != NULL && bodyB != NULL);
	if (physics) {
		bool movA = (bodyA->GetMass() > bodyB->GetMass());
		//								seperate objects apart from each other
		if (movA) {
			Transform bt = b.second->GetTransform();
			b.second->SetPosition(bt._position + sd._separationVector * (sd._penetrationDistance * 1.1f));
		}
		else {
			Transform at = a.second->GetTransform();
			a.second->SetPosition(at._position + sd._separationVector * (sd._penetrationDistance * -1.1f));
		}
	}
	else{
		Transform at = a.second->GetTransform();
		a.second->SetPosition(at._position + sd._separationVector * (sd._penetrationDistance * -0.6f));
		Transform bt = b.second->GetTransform();
		b.second->SetPosition(bt._position + sd._separationVector * (sd._penetrationDistance * 0.6f));
		
	}

	
	//								physics response
	if (!physics) {
		printf("THERES A PROBLEM A BODY WAS NULL\n");
		return;
	}

	Vec3 relativeVelocity = (*bodyB->GetVelocity()) - (*bodyA->GetVelocity());		
	float e = (bodyA->GetCoefRestitution() + bodyB->GetCoefRestitution()) * 0.5f;//std::min(bodyA->GetCoefRestitution(), bodyB->GetCoefRestitution());	
	float j = -(1.0f + e) * Vec3::Dot(relativeVelocity, sd._separationVector);		
	j /= (1.0f / bodyA->GetMass()) + (1.0f / bodyB->GetMass());						
	Vec3* velA = bodyA->GetVelocity();
	Vec3* velB = bodyB->GetVelocity();
	//(*bodyA->GetVelocity()) += j / ( bodyA->GetMass() * sd._separationVector);
	(*velA ) -= (j / bodyA->GetMass()) * sd._separationVector;
	//(*bodyB->GetVelocity()) -= j / (bodyB->GetMass() * sd._separationVector) ;
	(*velB) += (j / bodyB->GetMass()) * sd._separationVector;
}

/// <summary>
/// this can be skipped to ignore static objects
/// </summary>
/// <param name="model"></param>
void CollisionHandler::TranslateByModel() {
	for (int i = 0; i < _all_bounds->size(); i++) {
		auto pair = _all_bounds->at(i);
		pair.first->Translate2World(pair.second->GetModelMatrix());
	}
}
bool CollisionHandler::RayCast(Ray* ray, RayHitData& hitData, const Vec3& plane_origin, const Vec3& plane_normal) {
																				
	//find every plane															
	//check plane intersection													
	//use DOT product to check if intersection is within polygonal bounds of the plane
	
	float denom = Vec3::Dot(plane_normal, ray->_direction);
	if (denom >= 1e-6) {//0.000001
		Vec3 relVect =  plane_origin - ray->_position;	
		float distance = Vec3::Dot(relVect, plane_normal);
		float idk =  Vec3::Dot(ray->_direction, plane_normal);
		idk = distance / idk;
		printf(" distance %.3f \n", distance);			
		Utility::PrintVector(("Distance : " + std::to_string(idk) + " : pos ").c_str(), (ray->_position + (ray->_direction * idk)));
		return (distance >= 0);
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