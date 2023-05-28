#include "ColliisonTestGame.h"
#include "../../Graphics/Renderer.h"
#include "../../Graphics/Sprite.h"
#include "../../Math/BoxBounds.h"



CollisionTestGame::CollisionTestGame():Game() {
	_tests = new std::vector<TestState*>();
	BaseNode* a = new BaseNode(Vec3(450, 400, 0), Vec3(50, 50, 1), 0);
	a->AddComponent(new Sprite("Assets/Textures/default.png"));
	a->AddComponent(new BoxBounds());

	BaseNode* b = new BaseNode(Vec3(400, 400, 0), Vec3(50, 50, 1), 0);
	b->AddComponent(new Sprite("Assets/Textures/default.png"));
	b->AddComponent(new BoxBounds());
	
	
	_world->AddChild(a);
	
	_world->AddChild(b);

	CreateTests(a, b);
	_state = 0;
	_play = false;
	_current = _tests->at(_state);
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
void CollisionTestGame::HandleKeyInputs(int key, int action, int mods) {
	if (action == 2) return;
	if (action == 0) {
		std::cout << " key event called from tower defense " << "aaction " << action << " key " << key << " mods " << mods << "\n";
		switch (key)
		{

			//left
		case 263:
			PrevTest();
			break;
			//right
		case 262:
			NextTest();
			break;
			//space
		case 32:
			Play(!_play);
			break;
		default:
			break;
		}
		
	}
}
void CollisionTestGame::Update(float deltaTime) {
	Game::Update(deltaTime);
	if (!_play) return;
	_current->Update(deltaTime);
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





