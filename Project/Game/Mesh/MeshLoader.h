#ifndef MESH_LOADER_H
#define MESH_LOADER_H
#include "Mesh.h"
class MeshLoader {
private:

public :
	/// <summary>
	/// auto generate a flat diffuse lit plane
	/// </summary>
	/// <param name="resolution"></param>
	/// <param name="width"></param>
	/// <param name="height"></param>
	/// <returns></returns>
	static Mesh* GetPlane(const float resolution, const float width, const float height);
};
#endif // !MESH_LOADER_H
