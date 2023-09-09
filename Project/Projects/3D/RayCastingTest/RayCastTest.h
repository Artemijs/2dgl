#ifndef RAY_CAST_TEST_H
#define RAY_CAST_TEST_H

#include "../../../Game/Game.h"

class RayCastTest : public Game {


private:

public :
	RayCastTest();
	~RayCastTest();
	void Update(float deltaTime) override;
	void HandleKeyInputs(int key, int action, int mods) override;


};

#endif // !RAY_CAST_TEST_H


