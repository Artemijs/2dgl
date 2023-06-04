#ifndef COLLISION_HANDLER_H
#define COLLISION_HANDLER_H
#include "Bounds.h"
#include <vector>
/*
	write this down 4 jun - mas at work

*/
class CollisionHandler {
private:

public :
	static std::vector<const Bounds*>* _all_bounds;
	static void RegisterBounds(const Bounds* b);
	static void Update(const float deltaTime);
	static void Delete();
};


#endif // !COLLISION_HANDLER_H
