#ifndef MESH_LOADER_H
#define MESH_LOADER_H
#include "Mesh.h"
class MeshLoader {
private:

public :
	/// <summary>
	/// auto generate a flat diffuse lit plane RESOLUTION CHANGES SIZE, PLANE NO CENTERED ON ORIGIN you should fix that
	/// 
	/// </summary>
	/// <param name="resolution"> number of vertices in row and col of the plane</param>
	/// <param name="width">currently not used local space width of plane</param>
	/// <param name="height">currently not used local space height of plane</param>
	/// <returns></returns>
	static Mesh* GetPlane(const float resolution, const float width, const float height);
};
#endif // !MESH_LOADER_H
