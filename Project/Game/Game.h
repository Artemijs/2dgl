#ifndef GAME_H
#define GAME_H

#include "../Graphics/Graphic.h"
#include "../Graphics/Sprite.h"
#include "../Graphics/AnimatedSprite.h"
#include "../UI/Text.h"
#include "../UI/Button.h"
#include "../UI/Basewindow.h"
#include "BaseNode.h"
class Game {
protected:
	bool _switch;
	bool _isRunning;
public :
	static v1_5::BaseObject* _world;
	static BaseNode* test;
	//static v1_5::Graphic* _testG;
	
	Game();
	virtual ~Game();
	virtual void Update(float deltaTime);
	void Draw();
	void HandleMouseInputs(int btn, int action);
	virtual void HandleKeyInputs(int key, int action, int mods);
	bool IsRunning();
};
#endif