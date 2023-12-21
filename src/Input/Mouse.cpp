#include "Input/Mouse.h"
#include "Graphics/Renderer.h"
#include "Input/MouseEventHandler.h"



Mouse::Mouse() :_maxKeys(8){
	//_maxKeys = 8;
	_hidden = false;
	_allKeys = new std::vector<MouseKey>();
	_keysPressed = new std::vector<mkeyPress>();
	_keysUp = new std::vector<mkeyPress>();
	for (int i = 0; i < _maxKeys; i++) {
		MouseKey mk{ i, MouseKeyState::IDLE };
		_allKeys->push_back(mk);
	}
	_mDownCalls = new std::vector<std::pair<const unsigned int, mouse_call>>();
}


Mouse::~Mouse() {
	delete _allKeys;
	delete _keysPressed;
	delete _keysUp;
	delete _mDownCalls;
}

/// <summary>
/// right so the reason why i did it this way was to have an easy structure to shove
/// 
/// </summary>
/// <param name="deltaTime"></param>
void Mouse::Update(const float deltaTime) {

	//HANDLE TRANSITION FROM MOUSE held TO idle
	for (unsigned int i = 0; i < _keysUp->size(); ) {
		auto mk = &_keysUp->at(i);
		if (mk->first) {
			mk->second->_state = MouseKeyState::IDLE;
			_keysUp->erase(_keysUp->begin() + i);
			i--;
		}
		else {
			mk->first = true;
		}
		i++;
	}
	
	//HANDLE TRANSITION FROM MOUSE PRESSED TO MOUSE HELD
	for (unsigned int i = 0; i < _keysPressed->size(); ) {
		auto mk = &_keysPressed->at(i);
		if (mk->first) {
			mk->second->_state = MouseKeyState::KEY_DOWN;
			_keysPressed->erase(_keysPressed->begin() + i);
			i--;
		}
		else {
			mk->first = true;
		}
		i++;
	}


	//					GET MOUSE POSITION
	double x, y;
	glfwGetCursorPos(Renderer::instance()->GetWindow(), &x, &y);

	y = Renderer::instance()->GetWindowSize().y - y;
	_position.x = x;
	_position.y = y;
}


void Mouse::AddCallback(const unsigned int type, std::pair<const unsigned int, mouse_call> call) {

	if (type == 0) {
		_mDownCalls->push_back(call);
	}

}


void Mouse::CallCalls(const unsigned int type, const MouseKey* mk) {
	if (type == 0) {
		//mouse down callbacks

		//check if there is a callback for this key
		for (int i = 0; i < _mDownCalls->size(); i++) {
			auto call = _mDownCalls->at(i);
			if (call.first == mk->_id) {
				bool remove = call.second(_position);
			}
			if (remove) {
				_mDownCalls->erase(_mDownCalls->begin() + i);
				i--;
			}
		}
		
	}
}

void Mouse::SetCursorPos(const float& x, const float& y) {

	_position.x = x;
	_position.y = y;
	glfwSetCursorPos(Renderer::instance()->GetWindow(), x, y);

}


void Mouse::SetCursorPos(const Vec2& cursorpos) {

	_position = cursorpos;
	glfwSetCursorPos(Renderer::instance()->GetWindow(), _position.x, _position.y);

}


void Mouse::SetCursorHidden(const bool hidden) {

	_hidden = hidden;

	if (_hidden) {
		glfwSetInputMode(Renderer::instance()->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	}
	else {
		glfwSetInputMode(Renderer::instance()->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	}

}


/// <summary>
/// Handle mouse Button presses, MouseEvents and MouseCollision with UI
/// </summary>
/// <param name="btn"></param>
/// <param name="action"></param>
void Mouse::ButtonInput(const unsigned int btn, const unsigned int action) {
	
	if (action == GLFW_PRESS) {				
		MouseKey* mk = &_allKeys->at(btn);	
		mk->_state = MouseKeyState::KEY_DOWN;
		_keysPressed->push_back(mkeyPress(false, mk));
		//CALL EVENTS ON THIS KEY IF IT EXISTS
		CallCalls(0, mk);
		
	}
	else if (action == GLFW_RELEASE) {
		
		//			CHANGE THE STATE
		MouseKey* mk = &_allKeys->at(btn);
		//CALL EVENTS ON THIS KEY IF IT EXISTS
		CallCalls(1, mk);
		mk->_state = MouseKeyState::KEY_RELEASE;
		
		//			ADD IT TO A LIST OF KEYS TO THAT CHANGE THE STATE NEXT FRAME
		_keysUp->push_back(mkeyPress(false, mk));
		
		//			REMOVE FROM PRESSED KEYS IF ITS THERE
		auto itt = _keysPressed->begin();
		auto end = _keysPressed->end();
		while (itt != end) {
			if ((*itt).second->_id == mk->_id) {
				_keysPressed->erase(itt);
				break;
			}
			itt++;
		}

	}
}


MouseKey* Mouse::GetMouseKey(const unsigned int key) {
	if (key > _allKeys->size()) {
		printf("MOUSE KEY NOR FOUND \n");
		return NULL;
	}
	return &_allKeys->at(key);
}


Vec2 Mouse::GetPosition() {return _position;}
bool Mouse::IsHidden() {return _hidden;}
//MOUSE POS IN vec format for conveniece
Vec3 Mouse::GetMousePosV3() { return Vec3(_position.x, _position.y, 0); }