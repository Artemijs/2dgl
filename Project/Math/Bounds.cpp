#include "Bounds.h"
#include "../Util/Utility.h"
const unsigned int Bounds::_component_id = Utility::GetID();
const unsigned int Bounds::ID()const {
	return _component_id;
}
Bounds::Bounds(BoundsType bt): _type(bt), BaseComponent()  {
	_centerOfMass = Vec3();
}
const Vec3* Bounds::GetCenterOfMass() {
	return &_centerOfMass;
}