#ifndef COLISION_TEST_GAME_H
#define COLISION_TEST_GAME_H
#include "../../Game/Game.h"


class TestState {
protected:
	BaseNode* _a;
	BaseNode* _b;
public :
	TestState();
	TestState(BaseNode* a, BaseNode* b);
	~TestState();
	virtual void Reset() = 0;
	virtual void Update(const float deltaTime) = 0;
};

class TestOne : public TestState {
	float _xVal;
private:

public :
	TestOne(BaseNode* a, BaseNode* b);
	~TestOne();
	 void Reset() override;
	 void Update(const float deltaTime) override;

};

class TestTwo : public TestState {
private:
	float _xVal;
public:
	TestTwo(BaseNode* a, BaseNode* b);
	~TestTwo();
	void Reset() override;
	void Update(const float deltaTime) override;

};

class TestThree : public TestState {
private:
	float _yVal;
public:
	TestThree(BaseNode* a, BaseNode* b);
	~TestThree();
	void Reset() override;
	void Update(const float deltaTime) override;

};

class TestFour : public TestState {
private:
	float _yVal;
public:
	TestFour(BaseNode* a, BaseNode* b);
	~TestFour();
	void Reset() override;
	void Update(const float deltaTime) override;

};

class TestFive : public TestState {
private:

public:
	TestFive(BaseNode* a, BaseNode* b);
	~TestFive();
	void Reset() override;
	void Update(const float deltaTime) override;

};



class CollisionTestGame :public Game{
private:
	std::vector<TestState*>* _tests;
	TestState* _current;

	unsigned int _state;
	bool _play;
	float _ang;
	float _angVel;
	float _angChange;
	void CreateTests(BaseNode* a, BaseNode* b);
public :
	CollisionTestGame();
	~CollisionTestGame() override;
	void Rotate(const int dir);
	void Update(float deltaTime) override;
	void HandleKeyInputs(int key, int action, int mods) override;
	void NextTest();
	void PrevTest();
	void Play(const bool on);
};

#endif