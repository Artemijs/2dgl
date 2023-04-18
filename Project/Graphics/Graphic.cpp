#include "Graphic.h"
#include "Renderer.h"

	Graphic::Graphic() :
		_textureId(Renderer::instance()->LoadTexture("Assets/Textures/default.png")),
		_shader(Renderer::instance()->GetShader(0)),
		BaseComponent(true){
		//_textureId = v1_5::Renderer::instance()->LoadTexture("Assets/Textures/default.png");
		//_shader = Renderer::instance()->GetShader(0);
		//_isGraphic = true;
		Renderer::instance()->AddGraphic(this);
	}
	Graphic::~Graphic() {
		printf("delting graphic\n");
	}
	Graphic::Graphic(const char* path) :
		_textureId(Renderer::instance()->LoadTexture(path)),
		_shader(Renderer::instance()->GetShader(0)),
		BaseComponent(true)	{
		//_isGraphic = true;
		Renderer::instance()->AddGraphic(this);

	}

	/*void Graphic::Bind(Matrix4x4* model)const {
		
	}*/
	void Graphic::Draw(const Matrix4x4* model) const {
		Bind(model);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		Unbind();
	}
	void Graphic::Unbind()const {
		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);
		glUseProgram(0);
	}
