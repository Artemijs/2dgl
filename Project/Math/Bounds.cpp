#include "Bounds.h"
#include "../Util/Utility.h"
const unsigned int Bounds::_component_id = Utility::GetID();
const unsigned int Bounds::ID()const {
	return _component_id;
}