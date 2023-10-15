#include "MeshLoader.h"
#include "../../Graphics/Materials/MaterialSprite.h"
#include "../../Graphics/Renderer.h"


Mesh* MeshLoader::GetPlane(const float resolution, const float width, const float height) {

	
	std::vector<Vertex>* verts = new std::vector<Vertex>();

	//									find the vertices per row and column

	int vPerRow = (int)(resolution);
	int vPerCol = (int)(resolution);

	//									create each vertex

	for (float i = 0; i < vPerRow; i++) {
		for (float j = 0; j < vPerCol; j++) {
			Vec3 vPos = Vec3(i, 0, j);
			//uv.y is flipped 
			Vec2 uvPos = Vec2( i / (vPerRow - 1), 1- j / (vPerCol - 1));
			Vec3 normal = Vec3(0, 1, 0);
			verts->push_back(Vertex{vPos, normal, uvPos});
		}
	}
	
	//										create the index array

	const unsigned int indexCount = (vPerRow - 1) * (vPerCol - 1) * 6;
	std::vector<GLuint>* indices = new std::vector<GLuint>();

	int index = 0;
	for (int i = 0; i < vPerRow - 1; i++) {
		for (int j = 0; j < vPerCol - 1; j++) {
			//2 counter clockwise polygons
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


	//								OPENGL STUFF
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

	return m;

}


Mesh* MeshLoader::GetCube() {


	//									create each vertex
	std::vector<Vertex>* verts = new std::vector<Vertex> { 
		
		Vertex{Vec3(-0.1f, -0.1f,  0.1f)},
		Vertex{Vec3(-0.1f, -0.1f, -0.1f)},
		Vertex{Vec3(0.1f, -0.1f, -0.1f)},
		Vertex{Vec3(0.1f, -0.1f,  0.1f)},
		Vertex{Vec3(-0.1f,  0.1f,  0.1f)},
		Vertex{Vec3(-0.1f,  0.1f, -0.1f)},
		Vertex{Vec3(0.1f,  0.1f, -0.1f)},
		Vertex{Vec3(0.1f,  0.1f,  0.1f)}
	
	};

	//										create the index array
	std::vector<GLuint>* indices = new std::vector<GLuint>{

		0, 1, 2,
		0, 2, 3,
		0, 4, 7,
		0, 7, 3,
		3, 7, 6,
		3, 6, 2,
		2, 6, 5,
		2, 5, 1,
		1, 5, 4,
		1, 4, 0,
		4, 5, 6,
		4, 6, 7

	};

	BaseMaterial* bm = new MaterialSprite(Renderer::instance()->GetShader(7), "Assets/Textures/default.png");
	VAO* vao = new VAO();
	Mesh* m = new Mesh(verts, indices, bm, indices->size());


	//								OPENGL STUFF
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

	return m;

}



/*
	

// Vertices coordinates
Vertex vertices[] =
{ //               COORDINATES           /            COLORS          /           TexCoord         /       NORMALS         //
	Vertex{Vec3(-1.0f, 0.0f,  1.0f), Vec3(0.0f, 1.0f, 0.0f), Vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{Vec3(-1.0f, 0.0f, -1.0f), Vec3(0.0f, 1.0f, 0.0f), Vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
	Vertex{Vec3( 1.0f, 0.0f, -1.0f), Vec3(0.0f, 1.0f, 0.0f), Vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)},
	Vertex{Vec3( 1.0f, 0.0f,  1.0f), Vec3(0.0f, 1.0f, 0.0f), Vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)}
};

// Indices for vertices order
GLuint indices[] =
{
	0, 1, 2,
	0, 2, 3
};

Vertex lightVertices[] =
{ //     COORDINATES     //
	Vertex{Vec3(-0.1f, -0.1f,  0.1f)},
	Vertex{Vec3(-0.1f, -0.1f, -0.1f)},
	Vertex{Vec3(0.1f, -0.1f, -0.1f)},
	Vertex{Vec3(0.1f, -0.1f,  0.1f)},
	Vertex{Vec3(-0.1f,  0.1f,  0.1f)},
	Vertex{Vec3(-0.1f,  0.1f, -0.1f)},
	Vertex{Vec3(0.1f,  0.1f, -0.1f)},
	Vertex{Vec3(0.1f,  0.1f,  0.1f)}
};

GLuint lightIndices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7
};

*/
