#ifndef PHYSICS_OBJECT_H
#define PHYSICS_OBJECT_H
#include "../Game/BaseComponent.h"
#include "Matrix4x4.h"
#include "../Game/BaseNode.h"



class PhysicsObject : public BaseComponent{
private:	
				
	Transform* _parentTransform;	
	Vec3 _velocity;					
	Vec3 _acceleration;				
	Vec3 _angularVelocity;			
	Vec3 _angularAcceleration;		
	Vec3 _force;					
	float _linearDampening;			
	float _angularDampening;		
	float _cRestitution;			
	float _cFriction;				
	float _mass;
public:

	static const unsigned int _component_id;
	PhysicsObject(Transform* transform);
	const unsigned int ID() const override;
	void SetPhysData(const float mass = 1.0f,const Vec3& vel = Vec3(), const Vec3& accel = Vec3(), const Vec3& angVel = Vec3(), const Vec3& angAccel = Vec3(),
		const float linearDamp = 0.1f, const float angDamp = 0.1f, const float _cRest = 0.1f, const float _cFriction = 0.1f);
	void Update(const float deltaTime);
	void AddForce(const Vec3& force);
	Vec3* GetVelocity();
	Vec3* GetAcceleration();
	Vec3* GetAngularVelocity();
	Vec3* GetAngularAccelaration();
	Vec3* GetForce();
	float GetLinearDampening();
	float GetAngularDampening();
	float GetCoefRestitution();
	void SetCoefRestitution(const float& rest);
	float GetCoefFriction();
	float GetMass();
	void SetMass(float mass);


};


#endif // !PHYSICS_OBJECT
