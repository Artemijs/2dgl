#ifndef GAME_H
#define GAME_H
#include "BaseNode.h"
#include "Graphics/Graphic.h"
#include "Graphics/Sprite.h"
#include "MouseEventComponent.h"
#include "Input/Keyboard.h"
#include "Math/PhysicsWorld.h"
#include "Input/Mouse.h"
class Game {							
protected:								
	bool _switch;						
	bool _isRunning;			
	float _ang;					
	//static Keyboard* _keyboard;
	static Mouse* _mouse;
	static PhysicsWorld* _physWorld;


public :								
										
	static BaseNode* _world;			
	Game();								
	virtual ~Game();					
	virtual void Update(float deltaTime);
	void Draw();
	bool IsRunning();
	void Test();
	static PhysicsWorld* GetPhyscisWorld();
	static Mouse* GetMouse();

};
#endif