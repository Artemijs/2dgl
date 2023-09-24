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
	std::vector<Vertex>* verts = new std::vector<Vertex>();// = {
		//Vertex{Vec3(-0.5f,  -0.5f,  -1.0f), Vec3(0.0f, 0.0f, 0.0f), Vec2(0.0f, 0.0f)},
		//Vertex{Vec3(-0.5f,  -0.5f,  -1.0f), Vec3(0.0f, 0.0f, 0.0f), Vec2(0.0f, 0.0f)},
		//Vertex{Vec3(-0.5f,  -0.5f,  -1.0f), Vec3(0.0f, 0.0f, 0.0f), Vec2(0.0f, 0.0f)},
	//};
		
	//resolution / (width * height )= total vertex count
	//resolution / (width ) = total vertex count per row
	//resolution / (height )= total vertex count per col

	//create each vertex, find its position and its UV texture co ordinate
	int vPerRow = (int)(width);
	int vPerCol = (int)(height);
	for (int i = 0; i < vPerRow; i++) {
		for (int j = 0; j < vPerCol; j++) {
			Vec3 vPos = Vec3(i, 0, j);
			Vec2 uvPos = Vec2( i/width, j/height);
			Vec3 normal = Vec3(0, 1, 0);
			verts->push_back(Vertex{vPos, normal, uvPos});
		}
	}
	//FIGURE OUT THE INDICES HERE PLEASE
	//every 4 vertices there are 6 indices
	const unsigned int indexCount = (vPerRow - 1) * (vPerCol - 1);
	//GLuint* indices = new GLuint[indexCount];
	std::vector<GLuint>* indices = new std::vector<GLuint>(indexCount);

	int index = 0;
	for (int i = 0; i < vPerRow - 1; i++) {
		for (int j = 0; j < vPerCol - 1; j++) {
			indices->push_back(vPerRow * j + i);			//0
			indices->push_back(vPerRow * (j + 1) + i);		//2
			indices->push_back(vPerRow * j + (i + 1));		//1

			indices->push_back(vPerRow * (j + 1) + i);		//2
			indices->push_back(vPerRow * (j + 1) + (i + 1));//3
			indices->push_back(vPerRow * j + (i + 1));		//1
			


		}
	}
	BaseMaterial* bm = new MaterialSprite(Renderer::instance()->GetShader(7), "Assets/Textures/default.png");
	VAO* vao = new VAO();
	Mesh* m = new Mesh(verts, indices, bm, indexCount);
	vao->Bind();			
	VBO* vbo = new VBO((*verts));		
	EBO* ebo = new EBO((*indices));	

	vao->LinkAttrib(vbo, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);						//positions
	vao->LinkAttrib(vbo, 2, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));	//normals
	vao->LinkAttrib(vbo, 1, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));	//uvs

	vao->Unbind();
	vbo->Unbind();
	ebo->Unbind();
	m->InitGLData(vao, vbo, ebo);
	//m->SetMaterial(new MaterialSprite(Renderer::instance()->GetShader(7), "Assets/Textures/default.png"));
	return m;//m;

}