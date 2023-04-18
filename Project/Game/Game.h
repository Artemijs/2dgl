#ifndef GAME_H
#define GAME_H
#include "BaseNode.h"
#include "../Graphics/Graphic.h"
#include "../Graphics/Sprite.h"

class Game {
protected:
	bool _switch;
	bool _isRunning;
	
public :

	static BaseNode* _world;
	static Graphic* _testG;
	Game();
	virtual ~Game();
	virtual void Update(float deltaTime);
	void Draw();
	void HandleMouseInputs(int btn, int action);
	virtual void HandleKeyInputs(int key, int action, int mods);
	bool IsRunning();
};
#endif