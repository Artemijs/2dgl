#ifndef PHYSICS_WORLD_H
#define PHYSICS_WORLD_H
#include <vector>
#include "PhysicsObject.h"
class PhysicsWorld {

private:
	std::vector<PhysicsObject*>* _allBodies;
	Vec3 _gravity;

public :
	static const float MaxBodySize;
	static const float MinBodySize;

	static const float MaxDensity;
	static const float MinDensity;
	PhysicsWorld();
	~PhysicsWorld();
	
	void AddBody(PhysicsObject* obj);
	
	/// <summary>
	/// Gets the body and puts it into the body pointed passed in
	/// </summary>
	/// <param name="index">The id of the object</param>
	/// <param name="body"> Reference to a pointer the value of which gets set here or set to null if not found</param>
	/// <returns></returns>
	bool GetBody(const unsigned int index, PhysicsObject*& body);
	
	/// <summary>
	/// this does not delete physics objects from memory, that happens when the component gets deleted
	/// </summary>
	/// <param name="body"></param>
	void RemoveBody(const PhysicsObject* body);
	
	void Step(const float deltaTime);
	



};


#endif