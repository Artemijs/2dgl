#include "Model.h"

#include "../../Graphics/Renderer.h"

Model::Model(const char* file) : _filePath(file){

}
void Model::Draw(const Shader& shader, const Camera& cam) {
	// Go over all meshes and draw each one
	for (unsigned int i = 0; i < _meshes.size(); i++)
	{
		//meshes[i].Mesh::Draw(shader, camera, matricesMeshes[i]);
	}
}