#include "PhysicsWorld.h"

const float PhysicsWorld::MaxBodySize = 64.0f * 64.0f;
const float PhysicsWorld::MaxBodySize = 0.01f * 0.01f;

const float PhysicsWorld::MaxDensity = 21.4f;
const float PhysicsWorld::MinDensity = 0.5f;

PhysicsWorld::PhysicsWorld() {
	_gravity = Vec3(0, 9.81f, 0);
	_allBodies = new std::vector<PhysicsObject*>();
}
void PhysicsWorld::AddBody(PhysicsObject* obj) {
	_allBodies->push_back(obj);
}
bool PhysicsWorld::GetBody(const unsigned int index, PhysicsObject*& body) {
	if (index >= _allBodies->size()) {
		body = NULL;
		return false;
	}
	body = _allBodies->at(index);
	return true;

}