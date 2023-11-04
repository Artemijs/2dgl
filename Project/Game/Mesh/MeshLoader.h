#ifndef MESH_LOADER_H
#define MESH_LOADER_H
#include "Mesh.h"
#include "Model.h"
class MeshLoader {
private:

public :

	static Mesh* GetTerrain( const int width, const int height);
	static Mesh* GetPlane(const int width, const int height);
	static Mesh* GetCube();
	static void LoadModel(const char* filePath, Model*& model);
	//static 

};
#endif // !MESH_LOADER_H
