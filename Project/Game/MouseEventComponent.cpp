#include "MouseEventComponent.h"
#include "../Util/Utility.h"
	



const unsigned int MouseEvent::_component_id = Utility::GetID<MouseEvent>();


MouseEvent::MouseEvent(): _callbacks(new std::vector<std::vector<fpointer>*>()) {

	const unsigned int max = (unsigned int)(BtnEvent::end);
	for (int i = 0; i < max; ++i) {
		_callbacks->push_back(new std::vector<fpointer>());
	}
}	


MouseEvent::~MouseEvent() {

	const unsigned int maxcalls = (unsigned int)(BtnEvent::end);
	for (int i = 0; i < maxcalls; i++) {
		delete (_callbacks->at(i));
	}
	delete _callbacks;
}


const unsigned int MouseEvent::ID() const {
	return _component_id;
}


void MouseEvent::AddEvent(const fpointer &f, const BtnEvent eType) {
	_callbacks->at((int)eType)->push_back(f);
}


void MouseEvent::CallEvents(const BtnEvent be, const Vec3 mousepos)const  {

	auto events = _callbacks->at(int(be));
	for (int i = 0; i < events->size(); i++) {
		events->at(i)(mousepos);
	}
}