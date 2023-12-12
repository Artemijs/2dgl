#include "Projects/2D/TileMapMaterial.h"
#include "Graphics/Renderer.h"




TileMapMaterial::TileMapMaterial() :
	Material(new Shader("Projects/2D/TileMapEditorMain.vert", "Projects/2D/TileMapEditorMain.frag"), "Assets/Texturesdefault.png"),
	_tileSize(25.0f),
	_gridSize(100.0f),
	_gridLineSize(2),
	_gridColor(Vec3(1.0f, 1.0f, 1.0f)),
	_outlineSize(4),
	_outlineColor(Vec3(1.0f, 1.0f, 1.0f)),
	_selectedTile(Vec2(-1, -1)){

	UpdateShaderValues();
	HighlightTile(-1, -1);

}


TileMapMaterial::TileMapMaterial(float tileSize, float gridSize, Vec3 gridColor, float gridLineSize, float outlineSize, Vec3 outlineColor):
	_tileSize(tileSize),
	_gridSize(gridSize),
	_gridLineSize(gridLineSize),
	_gridColor(gridColor),
	_outlineSize(outlineSize),
	_outlineColor(outlineColor),
	_selectedTile(Vec2(-1, -1)),
	Material(new Shader("Projects/2D/TileMapEditorMain.vert", "Projects/2D/TileMapEditorMain.frag"), "Assets/Textures/default.png")
{
	UpdateShaderValues();
	HighlightTile(-1, -1);

}


TileMapMaterial::~TileMapMaterial() {
	printf("deleting TileMapMaterial \n");
	delete _shader;
}


void TileMapMaterial::Bind(const Matrix4x4* model) const {
	Material::Bind(model);
	//UpdateShaderValues();
	glUniformMatrix4fv(glGetUniformLocation(_shader->ID, "view"), 1, GL_TRUE,
		&Renderer::instance()->GetCamera()->GetViewMatrix()->buff[0]);
}


void TileMapMaterial::Unbind() const {
	Material::Unbind();

}


void TileMapMaterial::UpdateShaderValues() const {

	_shader->Activate();
	auto sId = _shader->ID;
	glUniform1f (glGetUniformLocation(sId, "_tileSize"), float(_tileSize / _gridSize));
	glUniform1f(glGetUniformLocation(sId, "_gridLineSize"), _gridLineSize/ _gridSize);
	glUniform3f (glGetUniformLocation(sId, "_gridColor"), _gridColor.x, _gridColor.y, _gridColor.z);
	//glUniform1f(glGetUniformLocation(sId, "_outlineSize"), _outlineSize);
	glUniform3f (glGetUniformLocation(sId, "_outlineColor"), _outlineColor.x, _outlineColor.y, _outlineColor.z);
	glUniform2f(glGetUniformLocation(sId, "_tileId"), _selectedTile.x, _selectedTile.y);
	glUseProgram(0);

}
void TileMapMaterial::HighlightTile(const float xId, const float yId) {
	//_selectedTile.x = xId;
	//_selectedTile.x = yId;
	_shader->Activate();
	glUniform2f(glGetUniformLocation(_shader->ID, "_tileId"), xId, yId);
	glUseProgram(0);
}