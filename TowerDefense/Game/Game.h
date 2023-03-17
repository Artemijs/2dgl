#ifndef GAME_H
#define GAME_H

#include "../Graphics/Graphic.h"
#include "../Graphics/Sprite.h"
#include "../Graphics/AnimatedSprite.h"
#include "../UI/Text.h"
#include "../UI/Button.h"
#include "../UI/Basewindow.h"

class Tile : public Button {
private:

public :
	Tile(const char* btnTxt, Vec3 pos, Vec3 size, float ang);
	~Tile();
};



class Game {
private:
	BaseObject* _world;
	Button* b;
	Button* b1;
	Button* b2;
	BaseWindow* w;
	BaseWindow* _gWindow;
	bool _isRunning;
	float x;

	Vec2Int _gridSize;
	std::vector<std::vector<Tile*>*>* _tiles;


public :

	//GRID
	void MakeGrid();



	Game();
	~Game();
	void Update(float deltaTime);
	void Draw();
	void HandleMouseInputs(int btn, int action);
	void HandleKeyInputs(int key, int action, int mods);
	bool IsRunning();
};
#endif