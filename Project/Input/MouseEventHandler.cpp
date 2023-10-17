#include "MouseEventHandler.h"
#include "../Game/Game.h"
#include "../Game/MouseEventComponent.h"
#include <iostream>
#include "../Math/Bounds.h"
#include "../UI/Button.h"
#define uwu 0x0
#define yes true
#define no false

//std::vector<MouseEvent*>* MouseEventHandler::_all_events = new std::vector < MouseEvent* >();
Vec3 MouseEventHandler::_prevPos = Vec3(0, 0, 0);
MouseEvent* MouseEventHandler::_current_m = uwu;
float MouseEventHandler::_time = 0;
float MouseEventHandler::_hover_time = 1.5f;
float MouseEventHandler::_ddclick_time = 0.5f;
float MouseEventHandler::_dd_time_max = 0.2f;
bool MouseEventHandler::_onHover = no;		
bool MouseEventHandler::_on = no;
BaseNode* MouseEventHandler::_current = uwu;
/*void MouseEventHandler::RegisterEvent(MouseEvent* e) {
	_all_events->push_back(e);
}
*/
#include "../Game/FBOComponent.h"
#include "../Math/CollisionDetection.h"
//48 39 46 
BaseNode* MouseEventHandler::CheckCollision(BaseNode* node, const Vec3 mousePos) {
	 //node->GetComponent<MouseEvent>(0);
	// printf("collision detection code not implemented\n");
	 Bounds* bb = node->GetComponent<Bounds>();
	 auto children = node->GetAllChildren();
	 BaseNode* closest_n = uwu;
	 //there is np check if there are mouse events or not
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
		 if(CollisionDetection::CheckPointSAT(mousePos, bb->GetShape()) != 0){
		 //if (bb->CheckInside(mousePos) ){
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
	
	//if nothing found
	if (newCurrent == uwu && _current == uwu) {
		return;
	}

	
	
	if (newCurrent != _current) {	
		//IF MOUSE OVER NEW THING	
		if (_current != uwu) {		
			MouseEvent* m = _current->GetComponent<MouseEvent>(MouseEvent::_component_id);
			if (m == NULL) return;
			m->CallEvents(BtnEvent::ON_LEAVE, mousePos);
			_current = uwu;
			_current_m = uwu;

		}						
		if (newCurrent != uwu) {
								
			MouseEvent* m = newCurrent->GetComponent<MouseEvent>(MouseEvent::_component_id);
			if (m == NULL) return;
			m->CallEvents(BtnEvent::ON_ENTER, mousePos);
			_current = newCurrent;
		}

	}
	else if (newCurrent == _current && _current != uwu) {
		//IF MOUSE STILL OVER OLD THING
		if (_prevPos == mousePos) {
			_time += deltaTime;
			if (_time >= _hover_time && !_onHover) {
				MouseEvent* m = _current->GetComponent<MouseEvent>(MouseEvent::_component_id);
				if (m == NULL) return;
				m->CallEvents(BtnEvent::ON_HOVER, mousePos);
				_onHover = yes;
			}
		}
		else {
			_time = 0;
			if (_onHover) {
				//_current->OnEndHover(&mousePos);
				MouseEvent* m = _current->GetComponent<MouseEvent>(MouseEvent::_component_id);
				if (m == NULL) return;
				m->CallEvents(BtnEvent::ON_END_HOVER, mousePos);
				_onHover = no;
			}
		}
	}
	_prevPos = mousePos;
}
void MouseEventHandler::HandleMouseClick(const bool on) {
	if (_current == uwu) return;
	MouseEvent* m = _current->GetComponent<MouseEvent>(MouseEvent::_component_id);
	if (m == NULL) return;
	if (on) {
		//_current->OnPressed(_prevPos);
		m->CallEvents(BtnEvent::ON_PRESS, _prevPos);
	}
	else if (!on) {
		//MouseEvent* m = _current->GetComponent<MouseEvent>(MouseEvent::_component_id);
		m->CallEvents(BtnEvent::ON_RELEASE, _prevPos);
		if (_ddclick_time != -1) {
			m->CallEvents(BtnEvent::ON_DOUBLE_CLICK, _prevPos);
			_ddclick_time = -1;
		}
		else {
			_ddclick_time = 0;
			m->CallEvents(BtnEvent::ON_CLICK, _prevPos);
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
	
}

const Vec3 MouseEventHandler::GetMousePosition() {
	return _prevPos;
}