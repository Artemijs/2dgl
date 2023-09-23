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

#include "../Game/Game.h"
#include "../Projects/TowerDefense/TowerDefenseGame.h"
#include "../Projects/CollisionTest/ColliisonTestGame.h"
#include "../Projects/CollisionTest/CollisionTesMain.h"
#include "../Projects/3D/RayCastingTest/RayCastTest.h"
#include "../Projects/ShaderTests/ShaterTest.h"
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
		default:
			std::cout << "YOu have entered a number out of range\n";
	}
	

}
Game* DevGetGameType() {

	int max = 6;

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



		switch (gameId) {
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
		default:
			g = new TowerDefenseGame();
		}

		
	}
	return g;
}