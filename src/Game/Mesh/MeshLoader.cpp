#include "Game/Mesh/Mesh.h"
#include "Graphics/Materials/MaterialSprite.h"
#include "Graphics/Renderer.h"
#include "Game/Mesh/Model.h"
#include "Game/Mesh/MeshLoader.h"

 std::vector<std::pair<const std::string, Model*>>* MeshLoader::_models;
 std::vector<unsigned char> MeshLoader::_data;
 json MeshLoader::JSON;


/// <summary>
/// Gets a 2d on the z x axis plane with VEC3 UP as normal MINIMUM OF 2 WIDTH AND HEIGHT
/// </summary>
/// <param name="width"> vertices  per row</param>
/// <param name="height">vertices per column</param>
/// <returns>Mesh* heap memory</returns>
Mesh* MeshLoader::GetTerrain(const int width, const int height) {


	std::vector<Vertex>* verts = new std::vector<Vertex>();

	//									find the vertices per row and column

	int vPerRow = (width);
	int vPerCol = (height);


	// 0( 0, 0, 0)		1 (1, 0 ,0)
	//
	// 2(0, 1, 0)		3 (1, 1, 0)				create each vertex
	Vec3 starPos = Vec3(0, 0, 0);// Vec3((float)(width * -0.5f), 0, (float)(width * -0.5f));
	Vec3 offset2Center = Vec3(0.5f, 0, 0.5f);//Vec3((float)((width - 1) * -0.5f), 0, (float)((width -1)* -0.5f));

	for (float i = 0; i < vPerRow; i++) {
		for (float j = 0; j < vPerCol; j++) {

			starPos = Vec3(j / (vPerCol - 1), 0, i / (vPerRow - 1)) - offset2Center;

			//uv.y is f1lipped 
			Vec2 uvPos = Vec2(1 - j / (vPerCol - 1), 1 - i / (vPerRow - 1));
			Vec3 normal = Vec3(0, 1, 0);

			verts->push_back(Vertex{ starPos, normal, uvPos });
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


/// <summary>
/// Gets a 2d on the z x axis plane with VEC3 UP as normal MINIMUM OF 2 WIDTH AND HEIGHT
/// </summary>
/// <param name="width"> vertices  per row</param>
/// <param name="height">vertices per column</param>
/// <returns>Mesh* heap memory</returns>
Mesh* MeshLoader::GetPlane(const int width, const int height) {


	std::vector<Vertex>* verts = new std::vector<Vertex>();

	//									find the vertices per row and column

	int vPerRow = (width);
	int vPerCol = (height);


	// 0( 0, 0, 0)		1 (1, 0 ,0)
	//
	// 2(0, 1, 0)		3 (1, 1, 0)				create each vertex
	Vec3 starPos = Vec3(0, 0, 0);// Vec3((float)(width * -0.5f), 0, (float)(width * -0.5f));
	Vec3 offset2Center = Vec3(0.5f, 0.5f, 0.0f);//Vec3((float)((width - 1) * -0.5f), 0, (float)((width -1)* -0.5f));
	
	for (float i = 0; i < vPerRow; i++) {
		for (float j = 0; j < vPerCol; j++) {
			
			starPos = Vec3(j/ (vPerCol-1), i/(vPerRow-1), 0.0f) - offset2Center;

			//uv.y is f1lipped 
			Vec2 uvPos = Vec2( j / (vPerCol - 1), i / (vPerRow - 1));
			Vec3 normal = Vec3(0, 0, 1.0f);

			verts->push_back(Vertex{starPos, normal, uvPos});
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

void MeshLoader::LoadModel(const char* filePath, Model*& model) {
	//check if exists
	/*for (int i = 0; i < _models->size(); i++) {
		auto val = _models->at(i);
		if (val.first.compare( filePath) == 0) {

			model = val.second;
			return;

		}
	}
	_models->push_back(std::pair<const std::string, Model*>{filePath, new Model()});

	// Make a JSON object
	std::string text = get_file_contents(filePath);
	JSON = json::parse(text);

	// Get the binary data
	Model::file = file;
	_data = GetData();

	// Traverse all nodes
	traverseNode(0);
	*/

}


void MeshLoader::TraverseNode(unsigned int nextNode, Matrix4x4 matrix ) {
	/*
	// Current node
	json node = JSON["nodes"][nextNode];

	// Get translation if it exists
	glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f);
	if (node.find("translation") != node.end())
	{
		float transValues[3];
		for (unsigned int i = 0; i < node["translation"].size(); i++)
			transValues[i] = (node["translation"][i]);
		translation = glm::make_vec3(transValues);
	}
	// Get quaternion if it exists
	glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
	if (node.find("rotation") != node.end())
	{
		float rotValues[4] =
		{
			node["rotation"][3],
			node["rotation"][0],
			node["rotation"][1],
			node["rotation"][2]
		};
		rotation = glm::make_quat(rotValues);
	}
	// Get scale if it exists
	glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
	if (node.find("scale") != node.end())
	{
		float scaleValues[3];
		for (unsigned int i = 0; i < node["scale"].size(); i++)
			scaleValues[i] = (node["scale"][i]);
		scale = glm::make_vec3(scaleValues);
	}
	// Get matrix if it exists
	glm::mat4 matNode = glm::mat4(1.0f);
	if (node.find("matrix") != node.end())
	{
		float matValues[16];
		for (unsigned int i = 0; i < node["matrix"].size(); i++)
			matValues[i] = (node["matrix"][i]);
		matNode = glm::make_mat4(matValues);
	}

	// Initialize matrices
	glm::mat4 trans = glm::mat4(1.0f);
	glm::mat4 rot = glm::mat4(1.0f);
	glm::mat4 sca = glm::mat4(1.0f);

	// Use translation, rotation, and scale to change the initialized matrices
	trans = glm::translate(trans, translation);
	rot = glm::mat4_cast(rotation);
	sca = glm::scale(sca, scale);

	// Multiply all matrices together
	glm::mat4 matNextNode = matrix * matNode * trans * rot * sca;

	// Check if the node contains a mesh and if it does load it
	if (node.find("mesh") != node.end())
	{
		translationsMeshes.push_back(translation);
		rotationsMeshes.push_back(rotation);
		scalesMeshes.push_back(scale);
		matricesMeshes.push_back(matNextNode);

		loadMesh(node["mesh"]);
	}

	// Check if the node has children, and if it does, apply this function to them with the matNextNode
	if (node.find("children") != node.end())
	{
		for (unsigned int i = 0; i < node["children"].size(); i++)
			traverseNode(node["children"][i], matNextNode);
	}
	*/
}

void MeshLoader::GetData(std::vector<unsigned char>& data) {
/*	std::string bytesText;
	std::string uri = JSON["buffers"][0]["uri"];

	std::string fileStr = std::string(_filePath);
	std::string fileDir = fileStr.substr(0, fileStr.find_last_of('/') + 1);
	bytesText = get_file_contents((fileDir + fileDir).c_str());
	data = std::vector<unsigned char >(bytesText.begin(), bytesText.end());
	*/
}


void MeshLoader::GetFloats(json accessor, std::vector<float>& floats) {

	unsigned int buffViewInd = accessor.value("bufferView", 1);
	unsigned int count = accessor["count"];
	unsigned int accByteOffset = accessor.value("byteOffset", 0);
	std::string type = accessor["type"];

	json bufferView = JSON["bufferViews"][buffViewInd];
	unsigned int byteOffset = bufferView["byteOffset"];

	unsigned int numPerVert;

	if (type == "SCALAR") numPerVert = 1;
	else if (type == "VEC2") numPerVert = 2;
	else if (type == "VEC3") numPerVert = 3;
	else if (type == "VEC4") numPerVert = 4;
	else throw std::invalid_argument("Type is invalid ( not SCALAR, VEC2, VEC3 OR VEC4)");

	unsigned int beginingOfData = byteOffset + accByteOffset;
	unsigned int lenghtOfData = count * 4 * numPerVert;

	for (unsigned int i = beginingOfData; i < beginingOfData + lenghtOfData;) {
		unsigned char bytes[] = { _data[i++], _data[i++], _data[i++], _data[i++] };
		float value;
		std::memcpy(&value, bytes, sizeof(float));
		floats.push_back(value);
	}
}


void MeshLoader::GetIndices(json accessor, std::vector<GLuint>& indices) {

	//std::vector<GLuint> indices;

	unsigned int buffViewInd = accessor.value("bufferView", 0);
	unsigned int count = accessor["count"];
	unsigned int accByteOffset = accessor.value("byteOffset", 0);
	unsigned int componentType = accessor["componentType"];

	json bufferView = JSON["bufferViews"][buffViewInd];
	unsigned int byteOffset = bufferView["byteOffset"];

	unsigned int beginingOfData = byteOffset + accByteOffset;
	if (componentType == 5125) {
		for (unsigned int i = beginingOfData; i < byteOffset + accByteOffset + count * 4; ) {
			unsigned char bytes[] = { _data[i++], _data[i++], _data[i++], _data[i++] };
			unsigned int value;
			std::memcpy(&value, bytes, sizeof(unsigned int));
			indices.push_back((GLuint)value);
		}
	}
	else if (componentType == 5123) {
		for (unsigned int i = beginingOfData; i < byteOffset + accByteOffset + count * 2; ) {
			unsigned char bytes[] = { _data[i++], _data[i++] };
			unsigned short value;
			std::memcpy(&value, bytes, sizeof(unsigned short));
			indices.push_back((GLuint)value);
		}
	}
	else if (componentType == 5122) {
		for (unsigned int i = beginingOfData; i < byteOffset + accByteOffset + count * 2; ) {
			unsigned char bytes[] = { _data[i++], _data[i++] };
			unsigned short value;
			std::memcpy(&value, bytes, sizeof(short));
			indices.push_back((GLuint)value);
		}
	}

}


void MeshLoader::GetTextures(std::vector<const Texture*>& textures) {
	/*Renderer* r = Renderer::instance();
	std::vector<Texture> textures;

	std::string fileStr = std::string(_filePath);
	std::string fileDirectory = fileStr.substr(0, fileStr.find_last_of('/') + 1);

	//for every texture used in the model
	unsigned int diffCount = 0;
	unsigned int specCount = 0;
	for (unsigned int i = 0; i < JSON["images"].size(); i++) {

		//get file path
		std::string path = JSON["images"][i]["uri"];

		std::string  texName;
		if (path.find("baseColor") != std::string::npos) {
			texName = "diffuse" + std::to_string(diffCount);
			diffCount++;
		}
		else if (path.find("metallicRoughness") != std::string::npos) {
			texName = "specular" + std::to_string(specCount);
			specCount++;
		}

		textures.push_back( r->LoadTexture(texName.c_str(), (fileDirectory + path).c_str()));


	}*/
}


void MeshLoader::AssembleVertices(std::vector<Vertex>& vertices, const std::vector<Vec3>& positions, const std::vector<Vec3>& normals, const std::vector<Vec2>& textUvs) {
	
	//tutorial time 1:46:33
	for (int i = 0; i < positions.size(); i++) {
		vertices.push_back
		(
			Vertex{
				positions[i],
				normals[i],
				textUvs[i]
			}
		);
	}
}



void MeshLoader::GroupFloatsVec2(const std::vector<float>& floatVec, std::vector<Vec2>& outVec) {
	for (int i = 0; i < floatVec.size(); i) {
		outVec.push_back(Vec2(floatVec[i++], floatVec[i++]));
	}
}

void MeshLoader::GroupFloatsVec3(const std::vector<float>& floatVec, std::vector<Vec3>& outVec) {
	for (int i = 0; i < floatVec.size(); i) {
		outVec.push_back(Vec3(floatVec[i++], floatVec[i++], floatVec[i++]));
	}
}


void MeshLoader::GroupFloatsVec4(const std::vector<float>& floatVec, std::vector<Vec4>& outVec) {
	for (int i = 0; i < floatVec.size(); i) {
		outVec.push_back(Vec4(floatVec[i++], floatVec[i++], floatVec[i++], floatVec[i++]));
	}
}


