#include "Game.h"
#include "../Graphics/Renderer.h"
#include "../Input/MouseEventController.h"
#include <iostream>
Game::Game() {
	Text::Init();
	_isRunning = true;

	_world = new BaseObject(Vec3(0, 0, -10), Vec3(1, 1, 1), Vec3(0,0,0));

	w = new BaseWindow(Vec3(400, 400, 1), Vec3(400, 400, 1), 0);
	_world->AddChild(w);

	b = new Button("New Game!", Vec3(-75, 0, 0.1f), Vec3(0.5f, 0.1f, 1), 0);
	b1 = new Button("Options", Vec3(-150 + 75, 80, 0.1f), Vec3(0.5f, 0.1f, 1), 0);
	b2 = new Button("Quit!", Vec3(-150 + 75, 40, 0.1f), Vec3(0.5f, 0.1f, 1), 0);
	w->AddChild(b);
	w->AddChild(b1);
	w->AddChild(b2);

	//GRID
	MakeGrid();

}
Game::~Game() {
	delete _world;
	delete w;
	delete b;
	delete b1;
	delete b2;
	delete _gWindow;
	for (int i = 0; i < _tiles->size(); i++) {
		for (int j = 0; j < _tiles->at(i)->size(); j++) {
			delete _tiles->at(i)->at(j);
		}
		delete _tiles->at(i);
	}
	delete _tiles;
	delete Renderer::instance();
	MouseEventController::Delete();
}
//remove all ui code
//add UpdateModelMatrix(parentPos, parentScale, parentRot)
//make every graphic object inherit from element


void Game::Update(float deltaTime) {
	//translate children 
	_world->MakeModelMatrix(Matrix4x4(1), Matrix4x4(1), Matrix4x4(1));
	//b->GetBounds()->Translate2World();
	_world->TryUpdate(deltaTime);
	x += 0.01f * deltaTime;
	
	double xpos, ypos;
	//s->SetPosition(s->GetPosition() + Vec3(0, x, 0));
	//_slider->Up
	//_animsprt->Update(deltaTime);


	//PHYSICS 
	//- update all model matrices( parentTransform, parentScale, parentRotation)
		
		
	//MOUSE EVENTS
	glfwGetCursorPos(Renderer::instance()->GetWindow(), &xpos, &ypos);
	ypos = Renderer::instance()->GetWindowSize().y - ypos;
	MouseEventController::HandleMouseMoving(Vec2(xpos, ypos), deltaTime);
	MouseEventController::Update(deltaTime);

	//KEYBOARD EVENTS


	
	
}
void Game::Draw() {
	//s->UpdateTransform(Matrix4x4(1));
	Renderer::instance()->Draw();
}


void Game::HandleKeyInputs(int key, int action, int mods) {
	if (action == GLFW_REPEAT) return;
	std::cout << " key event called "<<"aaction "<<action<<" key "<<key<<" mods "<<mods<<"\n";
	if (action == GLFW_PRESS) {
		

		std::cout << "key pressed \n";
		if (key == GLFW_KEY_A) {
			std::cout << "key A \n";
			w->SetVisible(false);
		}
	}
	else if (action == GLFW_RELEASE) {
		w->SetVisible(true);
		/*std::cout << "key released \n";
		if (key == GLFW_KEY_A) {
			std::cout << "key A \n";
		}*/
	}
}
void Game::HandleMouseInputs(int btn, int action) {
	std::cout << "btn event called \n";
	if (btn == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) 
		MouseEventController::HandleMouseClick(true);
	else if (btn == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
		MouseEventController::HandleMouseClick(false);
	}
}
bool Game::IsRunning() { return _isRunning; }




//GRID

void Game::MakeGrid(){
	
	//this needs to create a full screen transparent window
	_gWindow = new BaseWindow();
	w->AddChild(_gWindow);
	//tiles per row
	int tilespr = 2;
	Vec3 tileSize = Vec3(Renderer::instance()->GetWindowSize().x/ tilespr, Renderer::instance()->GetWindowSize().y/tilespr, 0);
	_tiles = new std::vector<std::vector<Tile*>*>();
	Vec3 pos = Vec3();
	for (int y = 0; y < tilespr; y++) {
		pos.y = y * tileSize.y;
		std::vector<Tile*>* row = new std::vector<Tile*>();
		pos.x = x * tileSize.x;
		for (int y = 0; y < tilespr; y++) {
			row->push_back(new Tile("", pos, tileSize, 0));
		}
		_tiles->push_back(row);
	}
	pos.x = 0;

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