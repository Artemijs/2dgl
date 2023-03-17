#include "MouseEventController.h"
#include <iostream>
#define uwu 0x0
std::vector<MouseEvent*>*  MouseEventController::_all_events = new std::vector < MouseEvent* >();
Vec2* MouseEventController::_prevPos = new Vec2(0, 0);
float MouseEventController::_time = 0;
float MouseEventController::_hover_time = 1.5f;
float MouseEventController::_ddclick_time = 0.5f;
float MouseEventController::_dd_time_max = 0.2f;
bool MouseEventController::_onHover = false;
bool MouseEventController::_on = false;
MouseEvent* MouseEventController::_current = uwu;
void MouseEventController::RegisterEvent(MouseEvent* e) {
	_all_events->push_back(e);
}

void MouseEventController::HandleMouseMoving(const Vec2 mousePos, const float deltaTime) {
	//call OnHover 3 25 6 08 59 1 7  iti is real
	//find all intersecting objects
	//a 64 bit integer has 64 bits, 64 1 or 0s in a line, assuming i wont have more than 64 objects
	//, assuming i wont have more than 64 objects i can bit shift to indicate which items in array are collided(1)
	if (_all_events->size() > 64) {
		std::cout << "MORE THAN 64 EVENTS, you are fucked\n";
		return;
	}
	unsigned int collided = 0;
	MouseEvent* newCurrent = uwu;
	//find all objects colliding with the mouse cursor
	for (int i = 0; i < _all_events->size(); ++i) {
		MouseEvent* m = _all_events->at(i);
		
		//CHECK IF OBJECT IS ON OR OFF 


		if (m->GetBounds()->CheckInside(Vec3(mousePos.x, mousePos.y, 0))) {
			collided = (collided | (m->GetBounds()->CheckInside(Vec3(mousePos.x, mousePos.y, 0)) << i));
		}
	}
	//find the closest to the camera object of all collided
	if (collided != 0) {
		//std::cout << collided << "\n";
		for (int i = 0; i < _all_events->size() ; ++i) {
			MouseEvent* m = _all_events->at(i);
			if (collided & (1 << i)) {
				
				if (newCurrent == uwu) {
					newCurrent = m;
				}
				else
				{
					float a = m->GetBounds()->GetZ() * 10;
					float b = newCurrent->GetBounds()->GetZ() * 10;
					if (a > b)
					{
						newCurrent = m;
						//_current->OnMouseEnter(&mousePos);
					}
				}
			}
		}
	}


	if (newCurrent != _current) {
		//IF MOUSE OVER NEW THING
		if (_current != uwu) {
			_current->OnMouseLeave(&mousePos);
			_current = uwu;
		}
		if (newCurrent != uwu) {
			_current = newCurrent;
			_current->OnMouseEnter(&mousePos);
		}

	}
	else if (newCurrent == _current && _current != uwu){
		//IF MOUSE STILL OVER OLD THING
		if ((*_prevPos) == mousePos) {
			_time += deltaTime;
			if (_time >= _hover_time && !_onHover) {
				_current->OnHover(&mousePos);
				_onHover = true;
			}
		}
		else {
			_time = 0;
			if (_onHover) {
				_current->OnEndHover(&mousePos);
				_onHover = false;
			}
		}
	}
	(*_prevPos) = mousePos;
}
void MouseEventController::HandleMouseClick(const bool on) {
	if (_current == uwu) return;

	if (on) {
		_current->OnPressed(_prevPos);
	}
	else if (!on) {
		_current->OnReleased(_prevPos);
		if (_ddclick_time != -1) {
			_current->OnDoubleClick(_prevPos);
			_ddclick_time = -1;
		}
		else {
			_ddclick_time = 0;
			_current->OnClick(_prevPos);
		}
	}
}
void MouseEventController::Update(const float deltaTime) {
	if (_current == uwu) return;
	if (_ddclick_time != -1) {
		_ddclick_time += deltaTime;
		if (_ddclick_time >= _dd_time_max) {
			_ddclick_time = -1;
		}
	}
	
}
void MouseEventController::Delete() {
	delete _prevPos;
	//for (int i = 0; i < _all_events->size(); ++i) {
		//delete _all_events->at(i);
	//}
	delete _all_events;
}

const Vec2* MouseEventController::GetMousePosition() {
	return _prevPos;
}