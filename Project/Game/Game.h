#ifndef GAME_H
#define GAME_H

#include "../Graphics/Graphic.h"
#include "../Graphics/Sprite.h"
#include "../Graphics/AnimatedSprite.h"
#include "../UI/Text.h"
#include "../UI/Button.h"
#include "../UI/Basewindow.h"

class Game {
private:
	BaseObject* _world;
	Button* b;
	Button* b1;
	Button* b2;
	BaseWindow* w;
	bool _isRunning;
	float x;
public :
	Game();
	~Game();
	void Update(float deltaTime);
	void Draw();
	void HandleMouseInputs(int btn, int action);
	void HandleKeyInputs(int key, int action, int mods);
	bool IsRunning();
};
#endif