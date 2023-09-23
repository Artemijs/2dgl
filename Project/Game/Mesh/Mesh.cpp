#include "Mesh.h"
#include "../../Util/Utility.h"

const unsigned int Mesh::_component_id = Utility::GetID();
const unsigned int Mesh::ID()const {
	return _component_id;
}

Mesh::Mesh() :Graphic() {
	
}

Mesh::Mesh(GLfloat* verts, GLuint* indices) : Graphic() {
	_vertices = verts;
	_indices = indices;
}

Mesh::Mesh(const unsigned int indexCount, VAO* vao, VBO* vbo, EBO* ebo, Material* mat) : 
	Graphic(mat, indexCount), _vao(vao), _vbo(vbo), _ebo(ebo){

}
Mesh::~Mesh() {
	printf("delteing mesh \n");
	_vao->Delete();
	delete _vao;
	//DOES THE EBO AND VBO NEED TO BE UNBOUND BEFORE DELETION?
	_ebo->Delete();
	delete _ebo;
	_vbo->Delete();
	delete _vbo;
	delete[] _vertices;
	delete[] _indices;
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

