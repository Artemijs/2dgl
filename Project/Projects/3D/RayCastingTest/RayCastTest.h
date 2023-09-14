#ifndef RAY_CAST_TEST_H
#define RAY_CAST_TEST_H

#include "../../../Game/Game.h"

class RayCastTest : public Game {


private:
	bool _3d;
	float _fov;
	float _near;
	float _far;
	float _aspect;
	BaseNode* bn1;
	float x;
public :
	RayCastTest();
	~RayCastTest();
	void Update(float deltaTime) override;
	void HandleKeyInputs(int key, int action, int mods) override;
	void ChangePerspective();


};

#endif // !RAY_CAST_TEST_H


