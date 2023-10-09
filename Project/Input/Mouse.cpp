#include "Mouse.h"
#include "../Graphics/Renderer.h"
#include "../Input/MouseEventHandler.h"



Mouse::Mouse() :_maxKeys(8){
	//_maxKeys = 8;
	_hidden = false;
	_allKeys = new std::vector<MouseKey>();
	_keysPressed = new std::vector<MouseKey*>();
	_keysUp = new std::vector<MouseKey*>();
	for (int i = 0; i < _maxKeys; i++) {
		MouseKey mk{ i, MouseKeyState::IDLE };
		_allKeys->push_back(mk);
	}
}


Mouse::~Mouse() {
	delete _allKeys;
	delete _keysPressed;
	delete _keysUp;
}

/// <summary>
/// right so the reason why i did it this way was to have an easy structure to shove
/// 
/// </summary>
/// <param name="deltaTime"></param>
void Mouse::Update(const float deltaTime) {

	//HANDLE TRANSITION FROM MOUSE held TO idle
	while (_keysUp->size() != 0) {
		MouseKey* mk = _keysUp->at(0);
		mk->_state = MouseKeyState::IDLE;
		_keysUp->erase(_keysUp->begin());
	}
	
	//HANDLE TRANSITION FROM MOUSE PRESSED TO MOUSE HELD
	for (unsigned int i = 0; i < _keysPressed->size(); ){
		
		//				change key state
		MouseKey* mk = _keysPressed->at(i);
		mk->_state = MouseKeyState::KEY_HELD;
		//_keysUp->push_back(mk);
		
		//			REMOVE IT FROM pressed array
		if (true)//I CAN EXPLAIN, THIS CODE IS FOR YOU
			_keysPressed->erase(_keysPressed->begin() + i);
		else i++;

	}


	//					GET MOUSE POSITION
	double x, y;
	glfwGetCursorPos(Renderer::instance()->GetWindow(), &x, &y);

	y = Renderer::instance()->GetWindowSize().y - y;
	_position.x = x;
	_position.y = y;

	//							THIS NEEDS TO BE MOVED 
	Renderer::instance()->GetCamera()->MouseMove();
	//							HANDLE UI MOUSE COLLISION AND EVENTS
	MouseEventHandler::HandleMouseMoving(Vec3(x, y, 0), deltaTime);
	MouseEventHandler::Update(deltaTime);

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
		_keysPressed->push_back(mk);		
	}
	else if (action == GLFW_RELEASE) {
		
		//			CHANGE THE STATE
		MouseKey* mk = &_allKeys->at(btn);
		mk->_state = MouseKeyState::KEY_UP;
		
		//			ADD IT TO A LIST OF KEYS TO THAT CHANGE THE STATE NEXT FRAME
		_keysUp->push_back(mk);
		
		//			REMOVE FROM PRESSED KEYS IF ITS THERE
		auto itt = _keysPressed->begin();
		auto end = _keysPressed->end();
		while (itt != end) {
			if ((*itt)->_id == mk->_id) {
				_keysPressed->erase(itt);
				break;
			}
			itt++;
		}

	}
	


	/*if (btn == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		MouseEventHandler::HandleMouseClick(true);
		//Renderer::instance()->GetCamera()->LockCursor(true);
	}
	else if (btn == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
		MouseEventHandler::HandleMouseClick(false);
		//Renderer::instance()->GetCamera()->LockCursor(false);
	}
	if (btn == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE) {
		//Renderer::instance()->GetCamera()->_x = !Renderer::instance()->GetCamera()->_x;
	}*/

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