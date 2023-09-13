#include "./ShaterTest.h"
#include "../../Graphics/Renderer.h";
#include "../../Graphics/Materials/DiffuseMaterial.h"
ShaderTest::ShaderTest() :Game(){
	//https://www.youtube.com/watch?v=ye_JlwUIyto&list=PL4neAtv21WOmIrTrkNO3xCyrxg4LKkrF7&index=16
	//do that next
	_time = 0;
	//create a plane
	Renderer* r = Renderer::instance();
	BaseNode* bn = new BaseNode(Vec3(400, 400, -5), Vec3(800, 800, 1), 0);

		
	Material* m = new MaterialUiSprite(r->GetShader(6), "Assets/Textures/default.png");
	m->_color = Vec4(1, 2, 3, 1);
	bn->AddComponent<Sprite>(new Sprite(m));
	_world->AddChild(bn);


	Shader *s  = r->GetShader(6);
	s->Activate();

	glUniform2f(glGetUniformLocation(s->ID, "iResolution"), r->GetWindowSize().x, r->GetWindowSize().y);
	glUniform1f(glGetUniformLocation(s->ID, "iTime"), _time);
	

}

ShaderTest::~ShaderTest() {

}

void ShaderTest::Update(float deltaTime) {
	Game::Update(deltaTime);
	_time += deltaTime;
	Shader* s = Renderer::instance()->GetShader(6);
	s->Activate();

	glUniform1f(glGetUniformLocation(s->ID, "iTime"), _time);
	glUseProgram(0);

	


}
void ShaderTest::HandleKeyInputs(int key, int action, int mods) {
	if (action == 2) return;
	if (action == 0) {
		std::cout << " key event called from tower defense " << "aaction " << action << " key " << key << " mods " << mods << "\n";
		switch (key)
		{
		case 32:
			DoThing();
			break;
		default:
			break;
		}

	}
}
void ShaderTest::DoThing() {
	
}