#include "TowerDefenseGame.h"
#include "../../Graphics/Renderer.h"
//TILE

Tile::Tile(const char* btnTxt, Vec3 pos, Vec3 size, float ang, BaseObject* parent):Button(btnTxt, pos, size, ang, parent) {
	
}
Tile::~Tile() {
	std::cout << "Deleting tile\n";
	
}





TowerDefenseGame::TowerDefenseGame():Game() {
	_t = new Tile("", Vec3(400,400, 0), Vec3(100, 100, 1), 0, _world);
	//_world->AddChild(_t);
	_s = new Sprite("./Assets/Textures/default.png", Vec3(100, 50, 0), Vec3(100, 40, 1), 0, _world);
	_world->AddChild(_s);
	
	_rn1 = new RenderNode(Vec3(0, 0, 0), Vec3(100, 400, 1), 0, _world);
	//_s1 = new Sprite("./Assets/Textures/default.png", Vec3(100, 50, 0), Vec3(100, 40, 1), 0, _rn1);
	//_s2 = new Sprite("./Assets/Textures/default.png", Vec3(100, 50, 0), Vec3(100, 40, 1), 0, _world);


	// 
	//MakeGrid();
}


TowerDefenseGame::~TowerDefenseGame() {
	std::cout << "deleting tower defense game\n";
	if(_tiles != NULL)
	for (int i = 0; i < _tiles->size(); i++) {
		for (int j = 0; j < _tiles->at(i)->size(); j++) {
			delete _tiles->at(i)->at(j);
		}
		delete _tiles->at(i);
	}
	delete _tiles;
	delete _t;
	delete _s;
	delete _rn1;
	delete _s1;
	delete _s2;
}


void TowerDefenseGame::HandleKeyInputs(int key, int action, int mods) {
	if (action == 2) return;
	std::cout << " key event called from tower defense " << "aaction " << action << " key " << key << " mods " << mods << "\n";
}
void TowerDefenseGame::Update(float deltaTime) {
	Game::Update(deltaTime);
	
}


//GRID

void TowerDefenseGame::MakeGrid() {
	_tiles = new std::vector<std::vector<Tile*>*>();
	_gridSize = Vec2Int(10, 10);
	//this needs to create a full screen transparent window
	//_gWindow = new BaseWindow();
	//w->AddChild(_gWindow);
	//tiles per row

	Vec3 tileSize = Vec3(Renderer::instance()->GetWindowSize().x / _gridSize.x, Renderer::instance()->GetWindowSize().y / _gridSize.y, 0);
	_tiles = new std::vector<std::vector<Tile*>*>();
	Vec3 pos = Vec3(0,0, -1);

	for (int y = 0; y < _gridSize.y; y++) {

		pos.y = y * tileSize.y;
		std::vector<Tile*>*row = new std::vector<Tile*>();
		
		for (int x = 0; x < _gridSize.x; x++) {

			pos.x = x * tileSize.x;
			Tile* t = new Tile("", pos, tileSize, 0, _world);
			_world->AddChild(t);

			row->push_back(t);
		}
		_tiles->push_back(row);
		pos.x = 0;
	}
	
	
}

/*
* small game
* grid of tiles
* towers
* enemies
* pathfinding
* 4 leveles
* main menu
* pause menu
* in game menu
*
*
*
*
*
* */