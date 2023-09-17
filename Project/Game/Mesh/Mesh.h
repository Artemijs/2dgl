#ifndef MESH_H
#define MESH_H

#include "../../BackEnd/VAO.h"
#include "../../Graphics/Graphic.h"

class Mesh : public Graphic{
private:
	VAO* _vao;
	Material* _material;
	static const unsigned int _component_id;
public:
	Mesh();
	Mesh(const unsigned int indexCount, VAO* vao, Material* mat);
	~Mesh();
	void Draw(const Matrix4x4* model) const override;
	VAO* GetVAO();
	const unsigned int ID() const override;
};
#endif