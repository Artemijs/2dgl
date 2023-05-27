#ifndef COLISION_TEST_GAME_H
#define COLISION_TEST_GAME_H
#include "../../Game/Game.h"



class CollisionTestGame :public Game{
private:

public :
	CollisionTestGame();
	~CollisionTestGame() override;
	void Update(float deltaTime) override;
//	void HandleKeyInputs(int key, int action, int mods) override;


};

#endif