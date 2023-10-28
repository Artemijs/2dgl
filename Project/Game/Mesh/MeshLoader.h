#ifndef MESH_LOADER_H
#define MESH_LOADER_H
#include "Mesh.h"
class MeshLoader {
private:

public :

	static Mesh* GetTerrain( const int width, const int height);
	static Mesh* GetPlane(const int width, const int height);
	static Mesh* GetCube();

};
#endif // !MESH_LOADER_H
