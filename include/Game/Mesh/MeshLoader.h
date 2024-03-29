#ifndef MESH_LOADER_H
#define MESH_LOADER_H
#include "Game/Mesh/Mesh.h"
#include "Game/Mesh/Model.h"
#include "json.h"
#include <string>
using json = nlohmann::json;




class MeshLoader {
private:
	static std::vector<std::pair<const std::string, Model*>>*  _models;
	static std::vector<unsigned char> _data;
	static json JSON;

	static void TraverseNode(unsigned int nextNode, Matrix4x4 matrix = Matrix4x4(1.0f));

	static void GetData(std::vector<unsigned char>& data);
	static void GetFloats(json accessor, std::vector<float>& floats);
	static void GetIndices(json accessor, std::vector<GLuint>& indices);
	static void GetTextures(std::vector<const Texture*>& textures);
	static void AssembleVertices(std::vector<Vertex>& vertices, const std::vector<Vec3>& positions, const std::vector<Vec3>& normals, const std::vector<Vec2>& textUvs);

	static void GroupFloatsVec2(const std::vector<float>& floatVec, std::vector<Vec2>& outVec);
	static void GroupFloatsVec3(const std::vector<float>& floatVec, std::vector<Vec3>& outVec);
	static void GroupFloatsVec4(const std::vector<float>& floatVec, std::vector<Vec4>& outVec);

public :

	static Mesh* GetTerrain( const int width, const int height);
	static Mesh* GetPlane(const int width, const int height);
	static Mesh* GetCube();
	static void LoadModel(const char* filePath, Model*& model);

	};
#endif // !MESH_LOADER_H
