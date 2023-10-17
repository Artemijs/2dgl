#include "Model.h"


Model::Model(const char* file) {
	std::string text = get_file_contents(file);
	JSON = json::parse(text);
	_filePath = file;
	_data = GetData();
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

std::vector<Vertex> Model::AssembleVertices(const std::vector<Vec3>& positions, const std::vector<Vec3>& normals, const std::vector<Vec2>& textUvs) {
	//tutorial time 1:39:33
	std::vector<Vertex> vertices;
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