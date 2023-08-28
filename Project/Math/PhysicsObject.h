#ifndef PHYSICS_OBJECT
#define PHYSICS_OBJECT
#include "../Game/BaseComponent.h"
#include "Matrix4x4.h"
class PhysicsObject : public BaseComponent{
private:
	static const unsigned int _component_id;
	PhysicsObject();				
	Vec3 _velocity;							
	Vec3 _acceleration;				
	Vec3 _angularVelocity;			
	Vec3 _angularAcceleration;		

	float _linearDampening;			
	float _angularDampening;		

	float _cRestitution;			
	float _cFriction;				
	
public:
	const unsigned int ID() const override;
	void SetPhysData(const Vec3& vel, const Vec3& accel, const Vec3& angVel, const Vec3& angAccel, const float linearDamp, const float angDamp, const float _cRest, const float _cFriction);
};


#endif // !PHYSICS_OBJECT
