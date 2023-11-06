#ifndef MODEL_H
#define MODEL_H

#include "../../Graphics/Renderer.h"
#include <json/json.h>
#include "Mesh.h"
using json = nlohmann::json;

class Model {
private:
	const char* _filePath;
	std::vector<unsigned char> _data;
	json JSON;

	std::vector<Mesh> _meshes;
	std::vector<Vec3> _translationMeshes;
	std::vector<Quaternion> _rotationsMeshes;
	std::vector<Vec3> _scalesMeshes;
	std::vector<Matrix4x4> _matricesMeshes;

	//std::vector<std::string> _loadedTexName;
	//std::vector<Texture> _loadedTex;

	void LoadMesh(unsigned int indMesh);
	
	

public :
	Model(const char* file);
	void Draw(const Shader& shader, const Camera& cam);
	
};

#endif // !MODEL_H
