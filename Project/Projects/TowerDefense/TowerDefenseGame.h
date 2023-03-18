#ifndef TOWERDEFENSEGAME_H
#define TOWERDEFENSEGAME_H
#include "../../Game/Game.h"
class TowerDefenseGame :public Game{
private:

public :
	TowerDefenseGame();
	~TowerDefenseGame() override;
	void Update(float deltaTime) override;
	void HandleKeyInputs(int key, int action, int mods) override;
};

#endif