#ifndef BOUNDS_H
#define BOUNDS_H

#define shape std::pair<const unsigned int, Vec3*>
//#include "CollisionDetection.h"
#include "Matrix4x4.h"
#include "Game/BaseComponent.h"
#include <functional>
#include <utility>
#include "Math/SeparationData.h"
#include "Game/BaseNode.h"
/// <summary>
/// total of 4 types, used to call different collision detection calls based on type
/// </summary>
enum class BoundsType{
	AABB = 0,
	BB,
	CIRCLE,
	TRIANGLE,
};

class Bounds: public BaseComponent {
protected:
	std::vector< Bounds*>* _activeCollisions;
	//all events
	std::vector<std::pair < Bounds*, std::function<void(Bounds* a, Bounds* b, SeparationData& sd)> >*>* _allEnterEvents;
	std::vector<std::pair < Bounds*, std::function<void( Bounds* a,  Bounds* b, SeparationData& sd )> >*>* _allExitEvents;

	std::pair < Bounds*, std::function<void( Bounds* a,  Bounds* b, SeparationData& sd)> >* FindEvent( Bounds* b, const bool enter);
	void CallEvent(const bool enter,  Bounds* b, SeparationData& sd);
	Matrix4x4 _offset;
public:
	static const unsigned int _component_id;
	bool _solid;
	bool _colliding;
	Vec3 _centerOfMass;
	const BoundsType _type;
	/// <summary>
	/// this variable isnt used yet i use solid to check if an object is moved when collisded with
	/// </summary>
	bool _isFixed;
	
	/// <summary>
	/// 
	/// </summary>
	/// <param name="bt">Bounds Type used in algorythms when working with generic Bounds and not inherited BoxBounds, Sphere, Etc</param>
	/// <param name="bn">Owner of the Bounds object, used for collision separation</param>
	Bounds(BoundsType bt, BaseNode* bn);
	virtual ~Bounds();
	virtual void Translate2World(const Matrix4x4* model)  = 0;
	const unsigned int ID() const override;
	virtual shape GetShape() = 0;
	const Vec3* GetCenterOfMass();
	const unsigned int IsColliding( Bounds* b);
	void AddActiveCollision(Bounds* b, SeparationData& sd);
	void RemoveActiveCollision(Bounds* b);
	/// <summary>
	/// add an event to allEnterEvents or allExitEvents
	/// </summary>
	/// <param name="enter">true for enter false for exit</param>
	/// <param name="e">LABUDA DURAIVUUUUU!</param>
	void AddEvent(const bool enter, std::pair < Bounds*, std::function<void( Bounds* a, Bounds* b, SeparationData& sd)> >* e);
	virtual float* GetSize() = 0;
	void SetOffset(const Matrix4x4& mat) {
		_offset = mat;
	}

	
};
#define CollisionEvent std::pair < Bounds*, std::function<void( Bounds* a,  Bounds* b, SeparationData& sd)> >
#endif // !BOUNDS_H

/*
	_allCollisions[0, 1, ... 45]
	AddCollidingWith(Bounds* b){
		_allCollisions->pushBack(b);
		if new bounds
		CallEvent(enter ,b);
	}
	pair<Bounds*, func_ptr> events;
	
	
	std::pair<Bounds*, func_ptr>* FindEvent(type, Bounds* b){
		eventsPtr = enterEvents;
		if(type == exit){
			eventsPtr = exitEvents;
		}
		for( int i =0; i < eventsPtr->Size(); ++i){
			pair<Bounds*, func_ptr>* e = events[i];
			if(e->first == b){
				return e;
			}
		}
	}

	CallEvent(type, b){
		if( type == enter){
			pair<Bounds*, func_ptr> e = FindEvent(type, b);
			if(e != null)
				e.second(data);
		}
	}

	EndCollision(Bound* b){
		remove b from the list of allCollisions
		CallEvent(exit, b);
	}

	OnColisionEnter(){
		for new events
			newEvent.OnEnter
			
	}
	//returns index of the data in all current stored collisions array or -1 if not found
	const unsigned int IsColliding(Bounds* b){
		for(int i =0; i < collisionSize; ++i){
			if(b == collisions->at(i))
				return i;
		}
		return -1;
	}


*/