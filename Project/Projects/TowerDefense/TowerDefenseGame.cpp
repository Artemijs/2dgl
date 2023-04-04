#include "TowerDefenseGame.h"
#include "../../Graphics/Renderer.h"
//TILE

Tile::Tile(const char* btnTxt, Vec3 pos, Vec3 size, float ang, BaseObject* parent):Button(btnTxt, pos, size, ang, parent) {
	
}
Tile::~Tile() {
	std::cout << "Deleting tile\n";
	
}





TowerDefenseGame::TowerDefenseGame():Game() {

	_speed = 0.4;
	_t = new Tile("", Vec3(400,400, 0), Vec3(100, 100, 1), 0, _world);
	//_world->AddChild(_t);
	_s = new Sprite("./Assets/Textures/default.png", Vec3(100, 50, 0), Vec3(100, 40, 1), 0, _world);
	_world->AddChild(_s);
	_rn1 = new RenderNode(Vec3(85, 400, 0), Vec3(150, 300, 1), 0, _world);
	_world->AddChild(_rn1);
	
	_s1 = new Sprite("./Assets/Textures/default.png", Vec3(100, 50, 0), Vec3(100, 40, 1), 0, _rn1);
	_rn1->AddChild(_s1);
	_s2 = new Sprite("./Assets/Textures/sliderBGdefault.png", Vec3(80, 100, 0), Vec3(130, 20, 1), 0, _world);
	_rn1->AddChild(_s2);

	_rn2 = new RenderNode(Vec3(650, 400, 0), Vec3(150, 750, 1), 0, _world);
	_world->AddChild(_rn2);
	_s3 = new Sprite("./Assets/Textures/sliderBGdefault.png", Vec3(80, 740, 0), Vec3(130, 20, 1), 0, _rn2);
	_rn2->AddChild(_s3);
	_s4 = new Sprite("./Assets/Textures/sliderBGdefault.png", Vec3(80, 715, 0), Vec3(130, 20, 1), 0, _rn2);
	_rn2->AddChild(_s4);
	
	
	_rn3 = new RenderNode(Vec3(0, 150, 0), Vec3(150, 300, 1), 0, _rn2);
	_rn2->AddChild(_rn3);
	_s5 = new Sprite("./Assets/Textures/sliderBGdefault.png", Vec3(75, 150, 0), Vec3(150, 300, 1), 0, _rn3);
	_rn3->AddChild(_s5);
	
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
	delete _s3;
	delete _s4;
	delete _s5;
	delete _rn2;
	delete _rn3;
}


void TowerDefenseGame::HandleKeyInputs(int key, int action, int mods) {
	if (action == 2) return;
	//Game::HandleKeyInputs(key, action, mods);
	//std::cout << " key event called from tower defense " << "aaction " << action << " key " << key << " mods " << mods << "\n";
	if (action == 0) {
		std::cout << " key event called from tower defense " << "aaction " << action << " key " << key << " mods " << mods << "\n";
		_switch = !_switch;
	}
}
void TowerDefenseGame::Update(float deltaTime) {
	Game::Update(deltaTime);
	/*Vec3 pos = _rn1->GetTransform()._position;
	Vec3 size = _rn1->GetTransform()._scale;
	float s = 0.1f;

	if (pos.y > 800 - size.y) {
		_speed = -s;
	}
	else if (pos.y < size.y) {
		_speed = s;
	}
	pos.y += _speed;
	_rn1->SetPosition(pos);*/
	Vec3 pos = _s->GetTransform()._position;
	Vec3 size = _s->GetTransform()._scale;
	float s = 0.2f;

	if (pos.x > 800 - size.x) {
		_speed = -s;
	}
	else if (pos.x < size.x) {
		_speed = s;
	}
	pos.x += _speed;
	_s->SetPosition(pos);
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