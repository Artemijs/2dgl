#include "TowerDefenseGame.h"

TowerDefenseGame::TowerDefenseGame() {

}
TowerDefenseGame::~TowerDefenseGame() {
	std::cout << "deleting tower defense game\n";
}
void TowerDefenseGame::HandleKeyInputs(int key, int action, int mods) {
	if (action == 2) return;
	std::cout << " key event called from tower defense " << "aaction " << action << " key " << key << " mods " << mods << "\n";
}
void TowerDefenseGame::Update(float deltaTime) {
	Game::Update(deltaTime);
	//std::cout << "tdGame update\n";
}