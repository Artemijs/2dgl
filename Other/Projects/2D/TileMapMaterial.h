#ifndef TILE_MAP_MATERIAL_H
#define TILE_MAP_MATERIAL_H
#include "Graphics/Materials/Material.h"


class TileMapMaterial : public Material {
private:
	Vec2 _selectedTile;
	float _outlineSize;
	Vec3 _outlineColor;
	
	Vec3 _gridColor;
	float _gridLineSize;

	float _tileSize;
	float _gridSize;

	

public :
	TileMapMaterial();
	TileMapMaterial(float tileSize, float gridSize, Vec3 gridLineColor, float gridLineSize, float outlineSize, Vec3 outlineColor);
	~TileMapMaterial();
	void Bind(const Matrix4x4* model)const override;
	void Unbind()const override;
	void UpdateShaderValues() const ;
	void HighlightTile(const float xId, const float yId);
};

#endif // !TILE_MAP_MATERIAL_H
