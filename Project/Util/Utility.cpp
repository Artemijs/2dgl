#include "Utility.h"
#include "../Game/FBOComponent.h"


unsigned int Utility::_idCount = 0;
bool Utility::IsRenderNode(const BaseNode* node) {
	const unsigned int fboCompSize = FBOComponent::_component_id;
	auto components = node->Components();
	if (components->size() != 1) return false;
	return (components->at(0)->first == fboCompSize);
}

const unsigned int Utility::GetID() 
{
	//id = sacii sum of type_info.name
	_idCount++;
	return _idCount;
	
}
const float Utility::Dist2CLosest(const float min, const float max, const float p) {
	const float min_m_p = min - ((p - min) * 2);
	const float max_m_p = max - p;
	if (min_m_p < max_m_p) {
		return min_m_p;
	}
	else
		return max_m_p;
}

float Utility::Deg2Rad(const float deg) {
	return deg * 0.0174533f;
}
float Utility::Rad2Deg(const float rad) {
	return  rad / 0.0174533f;
}







void Utility::PrintVector(const char* prefix, const Vec3& v) {
	std::cout << prefix << "(" << v.x << " ," << v.y << " ," << v.z << ")\n";
}
void Utility::PrintVector(const char* prefix, const Vec2& v) {
	std::cout << prefix << "(" << v.x << " ," << v.y <<  ")\n";
}
/*
	a = 10 
	b = 20 
	c = 13
	a - c =  -3
	b - c =  7 

	a = 1
	b = 25
	c = 23
	a - c =  -22
	b - c =  2

*/

void Utility::ToLower(std::string& s) {
	for (auto it = s.begin(); it != s.end(); it++) {
		(*it) = (std::tolower((*it)));
	}
}


void Utility::Swap(float* a, float* b, const int start, const int len) {

	for (int i = start; i < start + len; i++) {
		
		float temp = *(a + i);
		*(a + i) = *(b + i);
		*(b + i) = temp;
	}

}


void Utility::Swap(float* data, const int startA, const int startB, const int len) {

	for (int i = 0; i < len; i++) {

		float temp = *(data + (startA + i));
		*(data + (startA + i)) = *(data + (startA + i));
		*(data + (startB + i)) = temp;
		
	}

}

//													DEV FUNCTIONS
//----------------------------------------------------------------------------------------------------------

#include "../Game/Game.h"
#include "../Projects/TowerDefense/TowerDefenseGame.h"
#include "../Projects/CollisionTest/ColliisonTestGame.h"
#include "../Projects/CollisionTest/CollisionTesMain.h"
#include "../Projects/3D/RayCastingTest/RayCastTest.h"
#include "../Projects/ShaderTests/ShaterTest.h"
#include "../Projects/3D/MeshTest/MeshTest.h"
#include "../Projects/3D/3DCollision/CollisionTest3D.h"
#include "../Projects/2D/TopDownEditor.h"
#include <sstream>
void DevPrintHelp() {
	std::string msg = 
		"The games available to load are:\n";
	msg += "0 : TowerDefenseGame\n";
	msg += "1 : CollisionTestGame\n";
	msg += "2 : CollisionTestMain\n";
	msg += "3 : IneIntersectTest\n";
	msg += "4 : MaterialTest\n";
	msg += "5 : RayCastTest\n";
	msg += "6 : ShaterTest\n";
	msg += "7 : PhysicsTest\n";
	msg += "8 : MeshTest\n";
	msg += "9 : CollisionTest3D\n";
	msg += "10 : TopDownEditor\n";
	msg += "type HELP N n being the number of the game, for a description of that project\n";
	std::cout << msg;
}
void DevPrintDetails(std::string s) {
	s = s.substr(5, s.length());
	std::stringstream ss;
	ss << s;
	int nr = -1;
	ss >> nr;

	if (!ss) {
		std::cout << "please type a valid number after help, format : help(space)number\n";
		return;
	}
	switch (nr) {
		case 0:
			std::cout << "The tower defense game that this project was meant to be and designed in 2021\n nothing there yet and will probably throw an error\n";
			break;
		case 1:
			std::cout << "Collision test game that tests SAT with multiple different test cases.\n Us n and p keys to change tests, use space to pause and play\n";
			break;
		case 2:
			std::cout << "A Collision and Physics test game where you control a sphere, wasd to move\n";
			break;
		case 3:
			std::cout << "A test to test out a small line intersection algorythm, prints results to console\n";
			break;
		case 4:
			std::cout << "A game to test the materials of UI elements and to test transparency\n";
			break;
		case 5:
			std::cout << "A game to test RayCast in 3D\n";
			break;
		case 6:
			std::cout << "Tesing out funcy shader code i found online, PREPARE TO TRIP BALLS\n";
			break;
		case 7:
			std::cout << "Testing out the physics engine functions\n";
			break;
		case 8:
			std::cout << "Testing out mesh loading and viewing, camera 3d enabled, asd to move left click to rotate\n";
			break;
		case 9:
			std::cout << "Trying to figure out THE GEE JEE KAY algorythm.\n";
			break;
		case 10:
			std::cout << "TOP DOWN BACKGROUND EDITOR, WASD TO MOVE CAMERA.\n";
			break;
		default:
			std::cout << "YOu have entered a number out of range\n";
	}
	

}

Game* CreateNewGame(const unsigned int id) {
	Game* g = NULL;
	switch (id) {
	case 0:
		g = new TowerDefenseGame();
		break;
	case 1:
		g = new CollisionTestGame();
		break;
	case 2:
		g = new CollisionTestMain();
		break;
	case 3:
		g = new IneIntersectTest();
		break;
	case 4:
		g = new MaterialTest();
		break;
	case 5:
		g = new RayCastTest();
		break;
	case 6:
		g = new ShaderTest();
		break;
	case 7:
		g = new PhysicsTest();
		break;
	case 8:
		g = new MeshTest();
		break;
	case 9:
		g = new CollisionTest3D();
		break;
	case 10:
		g = new TopDownEditor();
		break;
	default:
		g = new TowerDefenseGame();
	}

	DevPrintDetails("help " + std::to_string(id));
	return g;
}
//		69
//	
//69 + 69 * 10^2 + 69 * 10^4 + 69 * 10^6
Game* DevGetGameType(const unsigned int id) {

	int funnyNumber = 69 + 69 * std::pow(10, 2) + 69 * std::pow(10, 4) + 69 * std::pow(10, 6);
	if (id != funnyNumber)return CreateNewGame(id);

	int max = 10;

	std::cout << "PLEASE ENTER WHICH GAME YOU WOULD LIKE TO LOAD \n____ a value between 0 and "<<max<<"\n Type HELP for details(no case sens)\n";
	Game* g = NULL;
	int gameId;
	std::stringstream ss;

	std::string input;
	while (g == NULL) {
		std::cin.clear();
		std::getline(std::cin, input);
		
		Utility::ToLower(input);
		if (input == "help") { // inout == help
			DevPrintHelp();
			continue;
		}
		else if (input.length() >= 6) { //input == help and a number
			if(input[0] == 'h' && input[3] == 'p' )
				DevPrintDetails(input);
			continue;
		}


		ss << input;
		ss >> gameId;
		if (!ss) {
			std::cout << "Please enter a valid number\n";
			continue;
		}

		std::cout << "Loading game " << input << "\n";

		g = CreateNewGame(gameId);
		
	}
	return g;
}