#ifndef GAME_H
#define GAME_H

#include "../Graphics/Graphic.h"
#include "../Graphics/Sprite.h"
#include "../Graphics/AnimatedSprite.h"
#include "../Graphics/Text.h"
#include "../UI/Button.h"
#include "../UI/UISprite.h"
#include "../UI/UIAnimatedSprite.h"
#include "../UI/UIText.h"
#include "../UI/UISlider.h"


class Game {
private:
	UIsprite* s;
	UIsprite* s1;
	
	Button* _b1;
	Button* _b2;
	UISlider* _slider;
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