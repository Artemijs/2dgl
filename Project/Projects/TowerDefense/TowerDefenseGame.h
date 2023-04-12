#ifndef TOWERDEFENSEGAME_H
#define TOWERDEFENSEGAME_H
#include "../../Game/Game.h"
#include "../../UI/RenderNode.h"


class TowerDefenseGame :public Game{
private:
	Vec2Int _gridSize;
	//std::vector<std::vector<Tile*>*>* _tiles;
//	Tile* _t;
	Sprite* _s;
	Sprite* _s1;
	Sprite* _s2;
	RenderNode* _rn1;
	
	Sprite* _s3;
	Sprite* _s4;
	RenderNode* _rn2;
	Sprite* _s5;
	RenderNode* _rn3;
	
	float _speed;
public :
	TowerDefenseGame();
	~TowerDefenseGame() override;
	void Update(float deltaTime) override;
	void HandleKeyInputs(int key, int action, int mods) override;

	//GRID
	void MakeGrid();

};

#endif