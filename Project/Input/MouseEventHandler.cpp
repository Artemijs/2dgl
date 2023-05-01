#include "MouseEventHandler.h"
#include "../Game/Game.h"
#include "../Game/MouseEventComponent.h"
#include <iostream>
#include "../Math/Bounds.h"
#define uwu 0x0
//std::vector<MouseEvent*>* MouseEventHandler::_all_events = new std::vector < MouseEvent* >();
Vec3 MouseEventHandler::_prevPos = Vec3(0, 0, 0);
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
BaseNode* MouseEventHandler::CheckCollision(BaseNode* node, const Vec3 mousePos) {
	 //node->GetComponent<MouseEvent>(0);
	// printf("collision detection code not implemented\n");
	 Bounds* bb = node->GetComponent<Bounds>();
	 auto children = node->GetAllChildren();
	 BaseNode* closest_n = uwu;

	 if (children != uwu) {
		 for (int i = 0; i < children->size(); ++i) {

			  BaseNode* bn = CheckCollision(children->at(i), mousePos);

			 if (bn == uwu) continue;

			 if (closest_n == NULL)
				 closest_n = bn;
			 else {
				 //buf[11] is the world space z value
				 
				 if (bn->GetModelMatrix()->buff[11] > closest_n->GetModelMatrix()->buff[11])
					 closest_n = bn;
			 }
		 }
	 }
	 if (bb != uwu) {
		 bb->Translate2World(node->GetModelMatrix());
		 if (bb->CheckInside(mousePos) ){
			 if (closest_n == uwu) {
				 return node;
			 }
			 else {
				 if (node->GetModelMatrix()->buff[11] > closest_n->GetModelMatrix()->buff[11]) {
					 //closest_n = node;
					 return node;
				 }		
			 }
		 }
		 else {
			 if (closest_n == uwu)	return uwu;
		 }
	 }
	 return closest_n;
	 //return uwu;
}

void MouseEventHandler::HandleMouseMoving(const Vec3 mousePos, const float deltaTime) {
	//call OnHover 3 25 6 08 59 1 7  iti is real
	//if(mousePos == (*_prevPos)
	BaseNode* newCurrent = CheckCollision(Game::_world, mousePos);
	if (newCurrent != NULL) printf("COLLIDED WITH SONETHING\n");
	if (newCurrent != _current) {
		//IF MOUSE OVER NEW THING
		if (_current != uwu) {
			//_current->OnMouseLeave(&mousePos);
			//MouseEvent<BaseComponent>::_id
			MouseEvent<Graphic>* m = _current->GetComponent<MouseEvent<Graphic>>(MouseEvent<Graphic>::_id);
			m->CallEvents(BtnEvent::ON_LEAVE);
			newCurrent = _current;
			//_current = uwu;
		}
		if (newCurrent != uwu) {
			_current = newCurrent;
			//_current->OnMouseEnter(&mousePos);

			//THIS RETURNS NULL MOUSE EVENT ID AND MOUSE EVENT COMPONENT VARIABLE ID DO NOT MATCH?
			printf("mouse event id is %d , %d\n" );
			 MouseEvent<Graphic>* m = _current->GetComponent<MouseEvent<Graphic>>(MouseEvent<Graphic>::_id);
			m->CallEvents(BtnEvent::ON_ENTER);
		}

	}
	else if (newCurrent == _current && _current != uwu) {
		//IF MOUSE STILL OVER OLD THING
		if (_prevPos == mousePos) {
			_time += deltaTime;
			if (_time >= _hover_time && !_onHover) {
				//_current->OnHover(&mousePos);
				 MouseEvent<Graphic>* m = _current->GetComponent<MouseEvent<Graphic>>(MouseEvent<Graphic>::_id);
				m->CallEvents(BtnEvent::ON_HOVER);
				_onHover = true;
			}
		}
		else {
			_time = 0;
			if (_onHover) {
				//_current->OnEndHover(&mousePos);
				 MouseEvent<Graphic>* m = _current->GetComponent<MouseEvent<Graphic>>(MouseEvent<Graphic>::_id);
				m->CallEvents(BtnEvent::ON_END_HOVER);
				_onHover = false;
			}
		}
	}
	_prevPos = mousePos;
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
	//delete _prevPos;
	//for (int i = 0; i < _all_events->size(); ++i) {
		//delete _all_events->at(i);
	//}
	//delete _all_events;
}

const Vec3 MouseEventHandler::GetMousePosition() {
	return _prevPos;
}