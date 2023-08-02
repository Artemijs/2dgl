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
	//collsiion data maybe?
	static void CallEvents(Bounds* a, Bounds* b, const SeparationData* sd);
public :
	static std::vector< std::pair<Bounds*, BaseNode*>>* _all_bounds;
	static void RegisterBounds( Bounds* b, BaseNode* bn);
	static void Update(const float deltaTime);
	static void CollisionSeparation(std::pair<Bounds*, BaseNode*>& a, std::pair<Bounds*, BaseNode*> &b, SeparationData& sd);
	static void Delete();
	
};


#endif // !COLLISION_HANDLER_H
