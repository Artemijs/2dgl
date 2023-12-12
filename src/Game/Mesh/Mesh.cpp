#include "Game/Mesh/Mesh.h"
#include "Util/Utility.h"
#include <cassert>



const unsigned int Mesh::_component_id = Utility::GetID();
const unsigned int Mesh::ID()const {
	return _component_id;
} 

Mesh::Mesh() :Graphic() {
	assert(false, "Used default constructor of MESH, behaviour undefined");
}

Mesh::Mesh(std::vector<Vertex>* verts, std::vector<GLuint>* indices, BaseMaterial* mat, const unsigned int indexCount) :
	Graphic(mat, indexCount),
	_vertices(verts),
	_indices(indices){
}
void Mesh::InitGLData(VAO* vao, VBO* vbo, EBO* ebo) {
	_vao = vao;
	_vbo = vbo;
	_ebo = ebo;
}
Mesh::~Mesh() {
	printf("delteing mesh \n");				
	delete _vertices;						
	delete _indices;						
	_vao->Delete();						
	delete _vao;						
	_vbo->Delete();					
	delete _vbo;				
	_ebo->Delete();				
	delete _ebo;			
}
#include "Graphics/Renderer.h"
void Mesh::Draw(const Matrix4x4* model) const {		
	//std::cout << "DRAWIN DROM MESH\n";	

	_baseMaterial->Bind(model);	

	_vao->Bind();					

	glDrawElements(GL_TRIANGLES, _indexCount, GL_UNSIGNED_INT, 0);

	_baseMaterial->Unbind();
	_vao->Unbind();
}
VAO* Mesh::GetVAO() { return _vao;  }

