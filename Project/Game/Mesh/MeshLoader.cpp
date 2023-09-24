#include "MeshLoader.h"
#include "../../Graphics/Materials/MaterialSprite.h"
#include "../../Graphics/Renderer.h"

Mesh* MeshLoader::GetPlane(const float resolution, const float width, const float height) {

	//do VBO AND VAO HAVE TO BE GLOBAL CACHED VARIABLES or can i delte them after vao is created?

	/*GLfloat* verts = new GLfloat[32]{
		//verices						//uvs
		-0.5f,  -0.5f,  -1.0f,			0.0f, 0.0f, //lower left

		-0.5f,   0.5f,	-1.0f,			0.0f, 1.0f,//upper left 

		0.5f,	 0.5f,	-1.0f,			1.0f, 1.0f, //upper right

		0.5f,	-0.5f,	-1.0f,			1.0f, 0.0f //lower right
	};*/
	std::vector<Vertex> verts;// = {
		//Vertex{Vec3(-0.5f,  -0.5f,  -1.0f), Vec3(0.0f, 0.0f, 0.0f), Vec2(0.0f, 0.0f)},
		//Vertex{Vec3(-0.5f,  -0.5f,  -1.0f), Vec3(0.0f, 0.0f, 0.0f), Vec2(0.0f, 0.0f)},
		//Vertex{Vec3(-0.5f,  -0.5f,  -1.0f), Vec3(0.0f, 0.0f, 0.0f), Vec2(0.0f, 0.0f)},
	//};
		
	//resolution / (width * height )= total vertex count
	//resolution / (width) = total vertex count per row
	//resolution / (height )= total vertex count per col

	//create each vertex, find its position and its UV texture co ordinate
	int vPerRow = (int)(width);
	int vPerCol = (int)(height);
	for (int i = 0; i < vPerRow; i++) {
		for (int j = 0; j < vPerCol; j++) {
			Vec3 vPos = Vec3(i, j, 0);
			Vec2 uvPos = Vec2( i/width, i/height);
			Vec3 normal = Vec3(0, 1, 0);
			verts.push_back(Vertex{vPos, normal, uvPos});
		}
	}
	//FIGURE OUT THE INDICES HERE PLEASE

	GLuint* indices = new GLuint[6]{
		0, 2, 1, //upper triangle,
		0, 3, 2 //lower triangle
	};

	/*Mesh* m  = new Mesh(verts, indices);
	VAO* vao = new VAO();
	vao->Bind();
	VBO* vbo = new VBO(verts, sizeof(GLfloat)*32);
	EBO* ebo;
	m->SetMaterial(new MaterialSprite(Renderer::instance()->GetShader(7), "Assets/Textures/default.png"));*/
	return NULL;//m;

}