#ifndef SHADER_TEST_H
#define SHADER_TEST_H

#include "../../Game/Game.h"

class ShaderTest : public Game {


private:
	float _time;
public :
	ShaderTest();
	~ShaderTest();
	void Update(float deltaTime) override;
	void HandleKeyInputs(int key, int action, int mods) ;
	void DoThing();


};

#endif 


