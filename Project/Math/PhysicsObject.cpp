#include "PhysicsObject.h"
#include "../Util/Utility.h"
PhysicsObject::PhysicsObject(Transform* transform) {
	_parentTransform = transform;
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
	_position = _parentTransform->_position;
	_rotation = _parentTransform->_angle;

}
void PhysicsObject::Update(const float deltaTime) {
	//UPDATE PHYSICS
	_position += _velocity * deltaTime;
	_rotation += _angularVelocity * deltaTime;

	//UPDATE THE TRANSFORM OF BASE NODE
	_parentTransform->_position = _position;
	_parentTransform->_angle = _rotation;

}