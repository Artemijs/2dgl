#ifndef VBO_CLASS_H
#define VBO_CLASS_H
#include <glad/glad.h>
#include "../Math/Matrix4x4.h"
#include <vector>
// Structure to standardize the vertices used in the meshes
struct Vertex
{
	Vec3 position;
	Vec3 normal;
	//Vec3 color;
	Vec2 texUV;
};



class VBO {

public :
	GLuint ID;
	VBO(std::vector<Vertex>& vertices);
	void Bind();
	void Unbind();
	void Delete();
};
#endif