#include "ColliisonTestGame.h"
#include "../../Graphics/Renderer.h"
#include "../../Graphics/Sprite.h"
#include "../../Math/BoxBounds.h"
/*
	beware of
	d ne budu
	molchim
	so what do we do now
	da mozhezh eto ne zapisovatj
	esli...
	english pls
	tak escho eto ne otoshlo
	so.. i remember this... 26 07 2019
	you can hear me
	oh ti menja slishish
	youve got a lon way to go
	piece oh shit should be saying the numbers
	ne gotov li ti
	so as you can see it has gotten very difficult to think now
	still waiting for you to satrt screaming at me
	i meant to say stop
	2021 is that you
	i dont even know who says any of these
	write this down for me
	I DONT GIVE A FUCK ABOUT MY PROBLEMS
	well seems like thats you
	that -situation- is unavoidable
	da bljat cho vi ebetesj, pomogli emu i vsjo
	what happened to the resy of you who were here a second ago
	ahujejesh
	he stopped writing it down
	you have problems here
	what kind of problems
	problems here aswell
	you heard me i said your name 
	that might have been 21
	zapisavai blja
	vsio zapisivai
	21 aprelja 2023
	2
	26 february 2021
	6 12 22 29 33 6 11 million 210

*/
//
#include "../../UI/Button.h"

CollisionTestGame::CollisionTestGame():Game() {
	_tests = new std::vector<TestState*>();
	BaseNode* a = new Button("a" ,Vec3(450, 400, 0), Vec3(200, 50, 1), 0);
	//a->AddComponent(new Sprite("Assets/Textures/default.png"));
	//a->AddComponent(new BoxBounds());

	BaseNode* b = new Button("b", Vec3(0, 0, 0), Vec3(50, 50, 1), 0);
	//b->AddComponent(new Sprite("Assets/Textures/default.png"));
	//b->AddComponent(new BoxBounds());
	
	
	_world->AddChild(a);
	
	_world->AddChild(b);

	CreateTests(a, b);
	_state = 0;
	_play = false;
	_current = _tests->at(_state);
	_angVel = 0;
	_ang = 0;
	_angChange = 2;
}


CollisionTestGame::~CollisionTestGame() {
	std::cout << "deleting CollisionDetection\n";
	for (int i = 0; i < _tests->size(); ++i) {
		delete _tests->at(i);
	}
	delete _tests;
}
//263 left
//262 right 
// 32 space 
#include "../../Math/CollisionDetection.h"
void CollisionTestGame::HandleKeyInputs(int key, int action, int mods) {
	if (action == 2) return;
	if (action == 0) {
		std::cout << " key event called from tower defense " << "aaction " << action << " key " << key << " mods " << mods << "\n";
		switch (key)
		{
		case 49:
			CollisionDetection::_print = true;
			//left
		case 263:
			Rotate(1);
			break;
			//right
		case 262:
			Rotate(-1);
			break;
			//space
		case 32:
			Play(!_play);
			break;
		case 78:
			PrevTest();
			break;
		case 80:
			NextTest();
			break;
		default:
			break;
		}
		
	}
}

void CollisionTestGame::Rotate(const int dir) {
	_angVel += _angChange* dir;
}

void CollisionTestGame::Update(float deltaTime) {
	Game::Update(deltaTime);
	if (!_play) return;
	_current->Update(deltaTime);

	if (_angVel != 0) {
		_ang += _angVel * deltaTime;

		_world->GetChild(0)->SetAngle(Vec3(0, _ang, 0));


	}

}

void CollisionTestGame::NextTest() {
	_play = false;
	_current->Reset();
	if (_state + 1 >= _tests->size()) return;
	_state++;
	_current = _tests->at(_state);
	
	_current->Reset();
}
void CollisionTestGame::PrevTest() {
	_play = false;
	_current->Reset();
	if (_state <= 0) return;
	_state--;
	_current = _tests->at(_state);
	//_play = false;
	_current->Reset();
}
void CollisionTestGame::Play(const bool on) {
	_play = on;
}
void CollisionTestGame::CreateTests(BaseNode* a, BaseNode* b) {
	_tests->push_back(new TestOne(a, b));
	_tests->push_back(new TestTwo(a, b));
	_tests->push_back(new TestThree(a, b));
	_tests->push_back(new TestFour(a, b));
	//_tests->push_back(new TestFive(a, b));
}
























TestState::TestState() {

}
TestState::TestState(BaseNode* a, BaseNode* b) : _a(a), _b(b) {

}
TestState::~TestState() {

}




TestOne::TestOne(BaseNode* a, BaseNode* b) : TestState(a, b) {
	_xVal = 15;
}

TestOne::~TestOne() {

}

void TestOne::Reset() {
	_a->SetPosition(Vec3(400, 400, 0)); 
	_b->SetPosition(Vec3(500, 400, 0)); 

}
void TestOne::Update(float deltaTime) {
	Vec3 bPos = _b->GetTransform()._position;
	bPos.x -= _xVal * deltaTime;
	_b->SetPosition(bPos);
}





TestTwo::TestTwo(BaseNode* a, BaseNode* b) : TestState(a, b) {
	_xVal = 15;

}

TestTwo::~TestTwo() {

}

void TestTwo::Reset() {
	_a->SetPosition(Vec3(400, 400, 0));
	_b->SetPosition(Vec3(300, 400, 0));
}

void TestTwo::Update(float deltaTime) {
	Vec3 bPos = _b->GetTransform()._position;
	bPos.x += _xVal * deltaTime;	
	_b->SetPosition(bPos);
}






TestThree::TestThree(BaseNode* a, BaseNode* b) : TestState(a, b) {
	_yVal = 50;
}
TestThree::~TestThree() {

}

void TestThree::Reset() {
	_a->SetPosition(Vec3(400, 400, 0));
	_b->SetPosition(Vec3(400, 600, 0));
}
void TestThree::Update(float deltaTime) {
	Vec3 bPos = _b->GetTransform()._position;
	bPos.y -= _yVal * deltaTime;
	_b->SetPosition(bPos);
}





TestFour::TestFour(BaseNode* a, BaseNode* b) : TestState(a, b) {
	_yVal = 50;
}
TestFour::~TestFour() {

}

void TestFour::Reset() {
	_a->SetPosition(Vec3(400, 400, 0));
	_b->SetPosition(Vec3(400, 200, 0));
}
void TestFour::Update(float deltaTime) {
	Vec3 bPos = _b->GetTransform()._position;
	bPos.y += _yVal * deltaTime;
	_b->SetPosition(bPos);
}





TestFive::TestFive(BaseNode* a, BaseNode* b) : TestState(a, b) {

}
TestFive::~TestFive() {

}

void TestFive::Reset() {

}
void TestFive::Update(float deltaTime) {

}





