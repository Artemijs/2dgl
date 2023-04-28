#include "MouseEventHandler.h"
#include "../Game/Game.h"
#include "../Game/MouseEventComponent.h"
#include <iostream>
#define uwu 0x0
//std::vector<MouseEvent*>* MouseEventHandler::_all_events = new std::vector < MouseEvent* >();
Vec2* MouseEventHandler::_prevPos = new Vec2(0, 0);
float MouseEventHandler::_time = 0;
float MouseEventHandler::_hover_time = 1.5f;
float MouseEventHandler::_ddclick_time = 0.5f;
float MouseEventHandler::_dd_time_max = 0.2f;
bool MouseEventHandler::_onHover = false;
bool MouseEventHandler::_on = false;
BaseNode* MouseEventHandler::_current = uwu;
/*void MouseEventHandler::RegisterEvent(MouseEvent* e) {
	_all_events->push_back(e);
}
*/
#include "../Game/FBOComponent.h"
 BaseNode* MouseEventHandler::CheckCollision(const BaseNode* node, const Vec2 mousePos) {
	 //node->GetComponent<MouseEvent>(0);
	return uwu;
}

void MouseEventHandler::HandleMouseMoving(const Vec2 mousePos, const float deltaTime) {
	//call OnHover 3 25 6 08 59 1 7  iti is real
	
	BaseNode* newCurrent = CheckCollision(Game::_world, mousePos);
	
	if (newCurrent != _current) {
		//IF MOUSE OVER NEW THING
		if (_current != uwu) {
			//_current->OnMouseLeave(&mousePos);
			//MouseEvent<BaseComponent>::_id
			_current->GetComponent<MouseEvent<Graphic>>(0);
			_current = uwu;
		}
		if (newCurrent != uwu) {
			_current = &(*newCurrent);
			//_current->OnMouseEnter(&mousePos);
		}

	}
	else if (newCurrent == _current && _current != uwu) {
		//IF MOUSE STILL OVER OLD THING
		if ((*_prevPos) == mousePos) {
			_time += deltaTime;
			if (_time >= _hover_time && !_onHover) {
				//_current->OnHover(&mousePos);
				_onHover = true;
			}
		}
		else {
			_time = 0;
			if (_onHover) {
				//_current->OnEndHover(&mousePos);
				_onHover = false;
			}
		}
	}
	(*_prevPos) = mousePos;
}
void MouseEventHandler::HandleMouseClick(const bool on) {
	if (_current == uwu) return;

	if (on) {
		//_current->OnPressed(_prevPos);
	}
	else if (!on) {
		//_current->OnReleased(_prevPos);
		if (_ddclick_time != -1) {
			//_current->OnDoubleClick(_prevPos);
			_ddclick_time = -1;
		}
		else {
			_ddclick_time = 0;
			//_current->OnClick(_prevPos);
		}
	}
}
void MouseEventHandler::Update(const float deltaTime) {
	if (_current == uwu) return;
	if (_ddclick_time != -1) {
		_ddclick_time += deltaTime;
		if (_ddclick_time >= _dd_time_max) {
			_ddclick_time = -1;
		}
	}

}
void MouseEventHandler::Delete() {
	delete _prevPos;
	//for (int i = 0; i < _all_events->size(); ++i) {
		//delete _all_events->at(i);
	//}
	//delete _all_events;
}

const Vec2* MouseEventHandler::GetMousePosition() {
	return _prevPos;
}