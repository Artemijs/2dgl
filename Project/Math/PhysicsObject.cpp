#include "PhysicsObject.h"
#include "../Util/Utility.h"
PhysicsObject::PhysicsObject() {

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
}