#include "MeshLoader.h"
#include "../../Graphics/Materials/MaterialSprite.h"
#include "../../Graphics/Renderer.h"

Mesh* MeshLoader::GetPlane() {

	//do VBO AND VAO HAVE TO BE GLOBAL CACHED VARIABLES or can i delte them after vao is created?

	/*GLfloat* verts = new GLfloat[32]{
		//verices						//uvs
		-0.5f,  -0.5f,  -1.0f,			0.0f, 0.0f, //lower left

		-0.5f,   0.5f,	-1.0f,			0.0f, 1.0f,//upper left 

		0.5f,	 0.5f,	-1.0f,			1.0f, 1.0f, //upper right

		0.5f,	-0.5f,	-1.0f,			1.0f, 0.0f //lower right
	};

	GLuint* indices = new GLuint[6]{
		0, 2, 1, //upper triangle,
		0, 3, 2 //lower triangle
	};
	Mesh* m  = new Mesh(verts, indices);
	VAO* vao = new VAO();
	vao->Bind();
	VBO* vbo = new VBO(verts, sizeof(GLfloat)*32);
	EBO* ebo;
	m->SetMaterial(new MaterialSprite(Renderer::instance()->GetShader(7), "Assets/Textures/default.png"));*/
	return NULL;//m;

}