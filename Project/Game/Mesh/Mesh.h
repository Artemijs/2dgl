#ifndef MESH_H
#define MESH_H

#include "../../BackEnd/VAO.h"
#include "../../BackEnd/VBO.h"
#include "../../BackEnd/EBO.h"
#include "../../Graphics/Graphic.h"


class Mesh : public Graphic {
private:
	VAO* _vao;
	VBO* _vbo;
	EBO* _ebo;
	GLfloat* _vertices;
	GLuint* _indices;
public:
	static const unsigned int _component_id;
	Mesh();
	Mesh(GLfloat* verts, GLuint* indices);
	Mesh(const unsigned int indexCount, VAO* vao, VBO* vbo, EBO* ebo, Material* mat);
	~Mesh();
	void Draw(const Matrix4x4* model) const override;
	VAO* GetVAO();
	const unsigned int ID() const override;
};
#endif