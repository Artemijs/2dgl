#include "Mesh.h"
#include "../../Util/Utility.h"

const unsigned int Mesh::_component_id = Utility::GetID();
const unsigned int Mesh::ID()const {
	return _component_id;
}

Mesh::Mesh() :Graphic() {
	
}
Mesh::Mesh(const unsigned int indexCount, VAO* vao, Material* mat) : 
	Graphic(indexCount), _vao(vao), _material(mat){

}
Mesh::~Mesh() {

}
void Mesh::Draw(const Matrix4x4* model) const {					
	std::cout << "DRAWIN DROM MESH\n";							
	_baseMaterial->Bind(model);									
	_vao->Bind();												
	glDrawElements(GL_TRIANGLES, _indexCount, GL_UNSIGNED_INT, 0);
	_baseMaterial->Unbind();
	_vao->Unbind();
}
VAO* Mesh::GetVAO() { return _vao;  }

