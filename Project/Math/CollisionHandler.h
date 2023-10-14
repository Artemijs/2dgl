#ifndef COLLISION_HANDLER_H
#define COLLISION_HANDLER_H
#include "Bounds.h"
#include <vector>
#include "CollisionDetection.h"
/*
	write this down 4 jun - mas at work

*/
class CollisionHandler {
private:

public :
	static std::vector< std::pair<Bounds*, BaseNode*>>* _all_bounds;
	static void RegisterBounds( Bounds* b, BaseNode* bn);
	/// <summary>
	/// Checks collision between objects every frame
	/// </summary>
	/// <param name="deltaTime">not really needed</param>
	static void Update(const float deltaTime);

	static void CollisionSeparation(std::pair<Bounds*, BaseNode*>& a, std::pair<Bounds*, BaseNode*> &b, SeparationData& sd);
	static void Delete();
	static bool RayCast(Ray* ray, RayHitData& hitData, const Vec3& plane_origin, const Vec3& plane_normal);
	
};


#endif // !COLLISION_HANDLER_H
