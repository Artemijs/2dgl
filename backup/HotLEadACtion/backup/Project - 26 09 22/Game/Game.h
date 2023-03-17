#ifndef GAME_H
#define GAME_H

#include "../Graphics/Graphic.h"
#include "../Graphics/AnimatedSprite.h"
#include "../Graphics/Text.h"
#include "../UI/Button.h"

class Game {
private:
	Graphic* _g;
	bool _isRunning;
	AnimatedSprite* _as;
	Text* _text;
	Button* _b;
	Button* _b1;
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