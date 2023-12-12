#ifndef MESH_H
#define MESH_H

#include "BackEnd/VAO.h"
#include "BackEnd/VBO.h"
#include "BackEnd/EBO.h"
#include "Graphics/Graphic.h"


class MeshMaterial : public Material {
private:

public :  

};
class Mesh : public Graphic {

private:
	VAO* _vao;
	VBO* _vbo;
	EBO* _ebo;

	std::vector<Vertex>* _vertices;
	std::vector<GLuint>* _indices;	

public:
	static const unsigned int _component_id;
	Mesh();
	Mesh(std::vector<Vertex>* verts, std::vector<GLuint>* indices, BaseMaterial* mat, const unsigned int indexCount);
	//Mesh(std::vector<Vertex> vertices, std::vector<);
	void InitGLData(VAO* vao, VBO* vbo, EBO* ebo);
	Mesh(const unsigned int indexCount, VAO* vao, Material* mat);
	~Mesh();
	void Draw(const Matrix4x4* model) const override;
	VAO* GetVAO();
	const unsigned int ID() const override;

};
#endif