#ifndef MESH_TEST_H
#define MESH_TEST_H




#include "Game/Game.h"

class MeshTest : public Game {


private:

	//Model* _model;

public:
	MeshTest();
	~MeshTest();
	void Update(float deltaTime) override;
	void MoveCamera();
};
#endif // !MESH_TEST_H
