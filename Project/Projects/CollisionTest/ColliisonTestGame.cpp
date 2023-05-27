#include "ColliisonTestGame.h"
#include "../../Graphics/Renderer.h"




CollisionTestGame::CollisionTestGame():Game() {

	
}


CollisionTestGame::~CollisionTestGame() {
	std::cout << "deleting CollisionDetection\n";
	
}


void CollisionTestGame::HandleKeyInputs(int key, int action, int mods) {
	if (action == 2) return;
	//Game::HandleKeyInputs(key, action, mods);
	//std::cout << " key event called from tower defense " << "aaction " << action << " key " << key << " mods " << mods << "\n";
	if (action == 0) {
		std::cout << " key event called from tower defense " << "aaction " << action << " key " << key << " mods " << mods << "\n";
		_switch = !_switch;
	}
}
void CollisionTestGame::Update(float deltaTime) {
	Game::Update(deltaTime);
	
}

