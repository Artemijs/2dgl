#ifndef GAME_H
#define GAME_H
#include "BaseNode.h"
#include "../Graphics/Graphic.h"
#include "../Graphics/Sprite.h"
#include "MouseEventComponent.h"
#include "../Input/Keyboard.h"
#include "../Math/PhysicsWorld.h"
class Game {							
protected:								
	bool _switch;						
	bool _isRunning;			
	float _ang;					
	//static Keyboard* _keyboard;
	static PhysicsWorld* _physWorld;

public :								
										
	static BaseNode* _world;			
	Game();								
	virtual ~Game();					
	virtual void Update(float deltaTime);
	void Draw();
	void HandleMouseInputs(int btn, int action);
	/// <summary>
	/// 
	/// </summary>
	/// <param name="key"></param>
	/// <param name="action"> 0 is mUp, 1 is mDown, 2 is mHeld</param>
	/// <param name="mods"></param>
	virtual void HandleKeyInputs(int key, int action, int mods);
	bool IsRunning();
	void Test();
	static PhysicsWorld* GetPhyscisWorld();

};
#endif