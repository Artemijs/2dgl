#include "Util/Utility.h"
#include "Game/Game.h"
#include "Graphics/Renderer.h"
#include "Projects/CollisionTest/CollisionTesMain.h"
#include "Projects/3D/RayCastingTest/RayCastTest.h"
Game* g;

void button_calls(GLFWwindow* window, int btn, int action, int mods) {
	if (g != NULL) {
		g->HandleMouseInputs(btn, action);
	}
}

void button_key_calls(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (g != NULL) {
		g->HandleKeyInputs(key, action, action);
	}
}
#include "./Projects/TowerDefense/TowerDefenseGame.h"
#include "./Projects/CollisionTest/ColliisonTestGame.h"
#include "./Projects/CollisionTest/CollisionTesMain.h"
#include "./Projects/3D/RayCastingTest/RayCastTest.h"
int main() {
	GLFWwindow* window = Renderer::instance()->GetWindow();
	//g = new Game();
	
	g = DevGetGameType();
	//g = new RayCastTest();
	
	
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glfwSetMouseButtonCallback(window, button_calls);
	glfwSetKeyCallback(window, button_key_calls);
	double prevFrame = glfwGetTime();

	while (g->IsRunning() && !glfwWindowShouldClose(window))
	{
		double crnFrame = glfwGetTime();
		float deltaTime = crnFrame - prevFrame;

		g->Update(deltaTime);
		g->Draw();

		prevFrame = crnFrame;
	}
	delete g;
	return 0;
}
