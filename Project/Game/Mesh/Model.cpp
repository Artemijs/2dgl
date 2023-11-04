#include "Model.h"


Model::Model(const char* file) {
	std::string text = get_file_contents(file);
	JSON = json::parse(text);
	_filePath = file;
	_data = GetData();
}

void Model::LoadMesh(unsigned int indMesh) {
	unsigned int posAccInd = JSON["meshes"][indMesh]["primitives"][0]["attributes"]["POSITION"];
	unsigned int normalAccInd = JSON["meshes"][indMesh]["primitives"][0]["attributes"]["NORMAL"];
	unsigned int uvAccInd = JSON["meshes"][indMesh]["primitives"][0]["attributes"]["TEXCOORD_0"];
	unsigned int indAccInd = JSON["meshes"][indMesh]["primitives"][0]["attributes"]["indices"];


	std::vector<float> posVec = GetFloats(JSON["accessors"][posAccInd]);
	std::vector<Vec3> positions = GroupFloatsVec3(posVec);

	std::vector<float> normalVec = GetFloats(JSON["accessors"][normalAccInd]);
	std::vector<Vec3> normals = GroupFloatsVec3(normalVec);

	std::vector<float> uvVec = GetFloats(JSON["accessors"][uvAccInd]);
	std::vector<Vec2> uvs = GroupFloatsVec2(uvVec);


	std::vector<Vertex> vertices = AssembleVertices(positions, normals, uvs);
	std::vector<GLuint> indices = GetIndices(JSON["accessors"][indAccInd]);
	std::vector<Texture> textures = GetTextures();


	//in order to make this work i have to create a material that stores these textures adnd does the draw call

	//_meshes.push_back(Mesh(vertices, indices, textures));
	//1:42:24



}
std::vector<unsigned char> Model::GetData() {
	std::string bytesText;
	std::string uri = JSON["buffers"][0]["uri"];

	std::string fileStr = std::string(_filePath);
	std::string fileDir = fileStr.substr(0, fileStr.find_last_of('/') + 1);
	bytesText = get_file_contents((fileDir + fileDir).c_str());
	std::vector<unsigned char > data(bytesText.begin(), bytesText.end());
	return data;
}


std::vector<float> Model::GetFloats(json accessor) {
	std::vector<float> floatVec;

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
		floatVec.push_back(value);
	}
	return floatVec;
}
std::vector<GLuint> Model::GetIndices(json accessor) {
	std::vector<GLuint> indices;

	unsigned int buffViewInd = accessor.value("bufferView", 0);
	unsigned int count = accessor["count"];
	unsigned int accByteOffset = accessor.value("byteOffset", 0);
	unsigned int componentType = accessor["componentType"];
	
	json bufferView = JSON["bufferViews"][buffViewInd];
	unsigned int byteOffset = bufferView["byteOffset"];

	unsigned int beginingOfData = byteOffset + accByteOffset;
	if (componentType == 5125) {
		for (unsigned int i = beginingOfData; i < byteOffset + accByteOffset + count * 4; ) {
			unsigned char bytes[] = {_data[i++], _data[i++], _data[i++], _data[i++]};
			unsigned int value;
			std::memcpy(&value, bytes, sizeof(unsigned int));
			indices.push_back((GLuint)value);
		}
	}
	else if (componentType == 5123) {
		for (unsigned int i = beginingOfData; i < byteOffset + accByteOffset + count * 2; ) {
			unsigned char bytes[] = {_data[i++], _data[i++]};
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
	return indices;

}


std::vector<Texture> Model::GetTextures() {
	std::vector<Texture> textures;

	std::string fileStr = std::string(_filePath);
	std::string fileDirectory = fileStr.substr(0, fileStr.find_last_of('/') + 1);

	
	for (unsigned int i = 0; i < JSON["images"].size(); i++) {

		std::string path = JSON["images"][i]["uri"];

		bool skip = false;
		for (unsigned int j = 0; j < _loadedTexName.size(); j++) {
			if (_loadedTexName[j] == path) {
				textures.push_back(_loadedTex[j]);
				skip = true;
				break;
			}
		}
		if (!skip) {
			if (path.find("baseColor") != std::string::npos) {
				Texture diffuse = Texture((fileDirectory + path).c_str(), "diffuse", _loadedTex.size());
				textures.push_back(diffuse);
				_loadedTex.push_back(diffuse);
				_loadedTexName.push_back(path);

			}
			else if (path.find("metallicRoughness") != std::string::npos) {
				Texture specular = Texture((fileDirectory + path).c_str(), "specular", _loadedTex.size());
				textures.push_back(specular);
				_loadedTex.push_back(specular);
				_loadedTexName.push_back(path);
			}
		}
	}
	return textures;
}

std::vector<Vertex> Model::AssembleVertices(const std::vector<Vec3>& positions, const std::vector<Vec3>& normals, const std::vector<Vec2>& textUvs) {
	//tutorial time 1:46:33
	std::vector<Vertex> vertices;

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
	return vertices;
}

std::vector<Vec2> Model::GroupFloatsVec2(const std::vector<float>& floatVec) {
	std::vector<Vec2> vectors;
	for (int i = 0; i < floatVec.size(); i) {
		vectors.push_back(Vec2(floatVec[i++], floatVec[i++]));
	}
	return vectors;
}
std::vector<Vec3> Model::GroupFloatsVec3(const std::vector<float>& floatVec) {
	std::vector<Vec3> vectors;
	for (int i = 0; i < floatVec.size(); i) {
		vectors.push_back(Vec3(floatVec[i++], floatVec[i++], floatVec[i++]));
	}
	return vectors;
}
std::vector<Vec4> Model::GroupFloatsVec4(const std::vector<float>& floatVec) {
	std::vector<Vec4> vectors;
	for (int i = 0; i < floatVec.size(); i) {
		vectors.push_back(Vec4(floatVec[i++], floatVec[i++], floatVec[i++], floatVec[i++]));
	}
	return vectors;
}

void Model::TraverseNode(unsigned int nextNode, Matrix4x4 matrix) {
	json node = JSON["nodes"][nextNode];

	Vec3 translation = Vec3();
	if (node.find("translation") != node.end()) {
		float transValues[3];
		for (unsigned int i = 0; i < node["translation"].size(); i++)
			transValues[i] = (node["translation"][i]);
		translation = Vec3(transValues[0], transValues[1], transValues[2]);
	}

	Quaternion rotation = Quaternion(1.0f, 0.0f, 0.0f, 0.0f);
	if (node.find("rotation") != node.end()) {
		rotation = Quaternion(node["rotation"][0], node["rotation"][1], node["rotation"][2], node["rotation"][3]);
	}

	Vec3 scale = Vec3(1.0f, 1.0f, 1.0f);
	if (node.find("scale") != node.end()) {
		scale = Vec3(node["scale"][0], node["scale"][1], node["scale"][2]);
	}

	Matrix4x4 matNode = Matrix4x4(1.0f);
	if (node.find("matrix") != node.end()) {
		//matNode.buff
		for (unsigned int i = 0; i < node["matrix"].size(); i++) {
			matNode.buff[i] = (node["matrix"][i]);
		}
	}

	Matrix4x4 trans = Matrix4x4(1.0f);
	Matrix4x4 rot = Matrix4x4(1.0f);
	Matrix4x4 sca = Matrix4x4(1.0f);

	trans = Matrix4x4::TranslationMatrix(translation);
	//rot = 1::44::47

}