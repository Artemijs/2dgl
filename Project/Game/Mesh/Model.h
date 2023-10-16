#ifndef MODEL_H
#define MODEL_H

#include "../../Graphics/Renderer.h"
#include <json/json.h>

using json = nlohmann::json;

class Model {
private:
	const char* _filePath;
	json JSON;


	std::vector<unsigned char> _data;
	std::vector<unsigned char> GetData();
	std::vector<float> GetFloats(json accessor);
	std::vector<GLuint> GetIndices(json accessor);

	std::vector<Vertex> AssembleVertices(const std::vector<Vec3>& positions, const std::vector<Vec3>& normals, const std::vector<Vec2> & textUvs);

	std::vector<Vec2> GroupFloatsVec2(const std::vector<float> &floatVec);
	std::vector<Vec3> GroupFloatsVec3(const std::vector<float>& floatVec);
	std::vector<Vec4> GroupFloatsVec4(const std::vector<float>& floatVec);

public :
	Model(const char* file);
	void Draw(const Shader& shader, const Camera& cam);
	
};

#endif // !MODEL_H
