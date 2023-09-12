#ifndef COLLISION_TES_MAIN_H
#define COLLISION_TES_MAIN_H
#include "../../Game/Game.h"



class CollisionTestMain :public Game{
private:
	
	bool _play;
	float _ang;
	float _angVel;
	BaseNode* _myNode;
	BaseNode* _otherNodes;

	
public :
	CollisionTestMain();
	~CollisionTestMain() override;
	void Update(float deltaTime) override;
	void HandleKeyInputs(int key, int action, int mods) override;
	void Play(const bool on);
	
};

class IneIntersectTest :public Game {
private:
public:
	IneIntersectTest();
	~IneIntersectTest() override;
	void Update(float deltaTime) override;
	void HandleKeyInputs(int key, int action, int mods) override;
	void Play(const bool on);
};


class MaterialTest :public Game {
private:
public:
	MaterialTest();
	~MaterialTest() override;
	void Update(float deltaTime) override;
	void HandleKeyInputs(int key, int action, int mods) override;
	void Play(const bool on);
	void Draw();
	void TestMaterials();
};


#endif