#ifndef MESH_LOADER_H
#define MESH_LOADER_H
#include "Mesh.h"
class MeshLoader {
private:

public :
	/// <summary>
	/// auto generate a flat diffuse lit plane 
	/// 
	/// </summary>
	/// 
	/// <param name="width">vertices per row</param>
	/// <param name="height">vertices per column</param>
	/// <returns></returns>
	static Mesh* GetPlane( const int width, const int height);
	static Mesh* GetCube();

};
#endif // !MESH_LOADER_H
