#include "Math/Bounds.h"
#include "Util/Utility.h"
#include "Math/CollisionHandler.h"

const unsigned int Bounds::_component_id = Utility::GetID();
const unsigned int Bounds::ID()const {
	return _component_id;
}
Bounds::Bounds(BoundsType bt, BaseNode* bn ):
	_solid(true), _type(bt), _colliding(false),
	_activeCollisions(new std::vector< Bounds*>()),
	_allEnterEvents(new std::vector<CollisionEvent*>()),
	_allExitEvents(new std::vector<CollisionEvent*>()),
	BaseComponent()  {
	_centerOfMass = Vec3(1, 1, 1);
	_isFixed = false;
	CollisionHandler::RegisterBounds(this, bn);
	_offset = Matrix4x4(1.0f);
	
}

Bounds::~Bounds() {
	printf("DELETING BASE BOUNDS\n");
	for (int i = 0; i < _allEnterEvents->size(); ++i) {
		delete _allEnterEvents->at(i);
	}
	delete _allEnterEvents;
	for (int i = 0; i < _allExitEvents->size(); ++i) {
		delete _allExitEvents->at(i);
	}
	delete _allExitEvents;
}




const Vec3* Bounds::GetCenterOfMass() {
	return &_centerOfMass;
}
/// <summary>
/// returns the collision event if exists
/// </summary>
/// <param name="b">the object colliding with</param>
/// <param name="enter">OnCollisionEnter(true) or OnCollisionExit(false)</param>
/// <returns>null if not found or std::pair<const Bounds*, lambda duraivu>*</returns>
CollisionEvent* Bounds::FindEvent( Bounds* b, const bool enter) {
	std::vector<CollisionEvent*>* events = _allEnterEvents;
	if (!enter) {
		events = _allExitEvents;
	}
	for (int i = 0; i < events->size(); ++i) {
		if (events->at(i)->first == b)
			return events->at(i);
	}
	return nullptr;
}
/// <summary>
/// finds the int index of bounds in the active collision array
/// </summary>
/// <param name="b"></param>
/// <returns>-1 if not found</returns>
const unsigned int Bounds::IsColliding( Bounds* b) {
	for (int i = 0; i < _activeCollisions->size(); ++i) {
		if (_activeCollisions->at(i) == b)
			return i;
	}
	return -1;
}

/// <summary>
/// calls the on collision entered and on collision exitted events
/// </summary>
/// <param name="enter">Enter or eXit events to call true or false</param>
/// <param name="b">the object collision is happening with</param>
/// <param name="sd">separation data from the collision detection algorythm</param>
void Bounds::CallEvent(const bool enter, Bounds* b, SeparationData& sd) {
	std::vector<CollisionEvent*>* events = _allEnterEvents;
	if (!enter) {
		events = _allExitEvents;
	}
	for (int i = 0; i < events->size(); ++i) {
		if (events->at(i)->first == b)
			events->at(i)->second(this, b, sd);
	}
}


void Bounds::AddActiveCollision( Bounds* b, SeparationData& sd) {
	_activeCollisions->push_back(b);
	//check if new collision or the collision has already happened
	if (IsColliding(b) != -1)   
		CallEvent(true, b, sd); 
		
}


/// <summary>
/// THIS IS GOING TO SHIT ITSELF because of iterators
/// </summary>
/// <param name="b"></param>
void Bounds::RemoveActiveCollision( Bounds* b) {

	SeparationData sd;
	CallEvent(false, b, sd);
	auto itt = _activeCollisions->begin();
	while ((*itt) != b && itt != _activeCollisions->end()) {
		itt++;
	}
	if (itt != _activeCollisions->end()) {
		//Maybe this doesnt shsit itself after all
		_activeCollisions->erase(itt);
	}

}
void Bounds::AddEvent(const bool enter, CollisionEvent* e) {
	if (enter) {
		_allEnterEvents->push_back(e);
	}
	else {
		_allExitEvents->push_back(e);
	}
}