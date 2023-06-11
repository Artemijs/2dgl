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
	static std::vector< Bounds*>* _all_bounds;
	static void RegisterBounds( Bounds* b);
	static void Update(const float deltaTime);
	static void CollisionSeparation(const Bounds* a, const Bounds* b, SeparationData& sd);
	static void Delete();
};


#endif // !COLLISION_HANDLER_H
