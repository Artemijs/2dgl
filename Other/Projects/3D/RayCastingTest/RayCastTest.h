#ifndef RAY_CAST_TEST_H
#define RAY_CAST_TEST_H

#include "Game/Game.h"

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
	void HandleKeyInputs(int key, int action, int mods);
	void ChangePerspective();
	void TurnCamera(const bool dir);
	/// <summary>
	/// moves the camera based of the int direction of moement
	/// </summary>
	/// <param name="dir">0 : w  1 : a  2 : s  3 : d </param>
	void MoveCamera(const unsigned int dir);


};

#endif // !RAY_CAST_TEST_H


