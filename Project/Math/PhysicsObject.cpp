#include "PhysicsObject.h"
#include "../Util/Utility.h"
#include "../Game/Game.h"
PhysicsObject::PhysicsObject(Transform* transform) {
	_parentTransform = transform;
	SetPhysData();
	_force = Vec3();
	Game::GetPhyscisWorld()->AddBody(this);
}

const unsigned int PhysicsObject::_component_id = Utility::GetID();
const unsigned int PhysicsObject::ID() const {
	return _component_id;
}

void PhysicsObject::SetPhysData(const Vec3& vel, const Vec3& accel, const Vec3& angVel, const Vec3& angAccel,
	const float linearDamp, const float angDamp, const float cRest, const float cFriction) {
	_velocity = vel;
	_acceleration = accel;
	_angularVelocity = angVel;
	_angularAcceleration = angAccel;
	_linearDampening = linearDamp;
	_angularDampening = angDamp;
	_cRestitution = cRest;
	_cFriction = cFriction;
	//_position = _parentTransform->_position;
	//_rotation = _parentTransform->_angle;


}
void PhysicsObject::Update(const float deltaTime) {
	//UPDATE PHYSICS
	_velocity += (_force + _acceleration ) * deltaTime;

	_parentTransform->_position += _velocity * deltaTime;
	_parentTransform->_angle += _angularVelocity * deltaTime;

	//RESET THE FORCE APPLIED making it apply only once
	_force = Vec3();

}
void PhysicsObject::AddForce(const Vec3& force) {
	_force += force;
}