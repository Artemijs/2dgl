#include "TileMapMaterial.h"
#include "../../Graphics/Renderer.h"



TileMapMaterial::TileMapMaterial() :
	Material(new Shader("Projects/2D/TileMapEditorMain.vert", "Projects/2D/TileMapEditorMain.frag"), "Assets/Texturesdefault.png"),
	_tileSize(25.0f),
	_gridSize(100.0f),
	_gridLineSize(2),
	_gridColor(Vec3(1.0f, 1.0f, 1.0f)),
	_outlineSize(4),
	_outlineColor(Vec3(1.0f, 1.0f, 1.0f)){

	UpdateShaderValues();

}


TileMapMaterial::TileMapMaterial(float tileSize, float gridSize, Vec3 gridColor, unsigned int gridLineSize, unsigned int outlineSize, Vec3 outlineColor):
	_tileSize(tileSize),
	_gridSize(gridSize),
	_gridLineSize(gridLineSize),
	_gridColor(gridColor),
	_outlineSize(outlineSize),
	_outlineColor(outlineColor),
	Material(new Shader("Projects/2D/TileMapEditorMain.vert", "Projects/2D/TileMapEditorMain.frag"), "Assets/Textures/default.png")
{
	UpdateShaderValues();

}


TileMapMaterial::~TileMapMaterial() {
	printf("deleting TileMapMaterial \n");
	delete _shader;
}


void TileMapMaterial::Bind(const Matrix4x4* model) const {
	Material::Bind(model);
	
	glUniformMatrix4fv(glGetUniformLocation(_shader->ID, "view"), 1, GL_TRUE,
		&Renderer::instance()->GetCamera()->GetViewMatrix()->buff[0]);
}


void TileMapMaterial::Unbind() const {
	Material::Unbind();

}


void TileMapMaterial::UpdateShaderValues() {

	auto sId = _shader->ID;
	glUniform1f (glGetUniformLocation(sId, "_tileSize"), _tileSize/_gridSize );
	glUniform1ui(glGetUniformLocation(sId, "_gridLineSize"), _gridLineSize);
	glUniform3f (glGetUniformLocation(sId, "_gridColor"), _gridColor.x, _gridColor.y, _gridColor.z);
	glUniform1ui(glGetUniformLocation(sId, "_outlineSize"), _outlineSize);
	glUniform3f (glGetUniformLocation(sId, "_outlineColor"), _outlineColor.x, _outlineColor.y, _outlineColor.z);

}