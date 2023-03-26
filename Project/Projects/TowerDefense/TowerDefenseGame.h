#ifndef TOWERDEFENSEGAME_H
#define TOWERDEFENSEGAME_H
#include "../../Game/Game.h"

class Tile : public Button {
private:

public:
	Tile(const char* btnTxt, Vec3 pos, Vec3 size, float ang, BaseObject* parent);
	~Tile();
};


class TowerDefenseGame :public Game{
private:
	Vec2Int _gridSize;
	std::vector<std::vector<Tile*>*>* _tiles;
	Tile* _t;
public :
	TowerDefenseGame();
	~TowerDefenseGame() override;
	void Update(float deltaTime) override;
	void HandleKeyInputs(int key, int action, int mods) override;

	//GRID
	void MakeGrid();

};

#endif