#ifndef TOP_DOWN_EDITOR_H
#define TOP_DOWN_EDITOR_H
#include "../../Game/Game.h"
#include "../../Util/MemoryManager.h"
#include "./TileMapMaterial.h"



class TopDownEditor : public Game {

private:
	const unsigned int _widthBTBG;
	const unsigned int _heightBTBG;
	float _tileSize;
	BaseNode* _mainTileMesh;
	TileMapMaterial* _tileMapMat;
	bool _moveOver;
	void CreateNew();
public :
	TopDownEditor();
	~TopDownEditor();
	
	void Update(float deltaTime) override;
	void MoveCamera3D(bool rotate = true, bool move = true);
	void MoveCamera2D();
	/// <summary>
	/// higlhlight the tile hovered over
	/// </summary>
	void HandleMouseMove();
	void OnMouseLeave(const Vec3& mPos);
	//void HighlighTiles(unsigned int tileId);

};











class TesObject : public Memory {
public:
	int test;
	int* testPtr;
	TesObject();
	~TesObject() override;
};



class TesObjecTChild : public TesObject {
public:
	TesObjecTChild();
	~TesObjecTChild() override;
};



class GarbageCollectorTest : public Game {
private:

public:
	GarbageCollectorTest();
	~GarbageCollectorTest();

	void Update(float deltaTime) override;
};


class QuaternionTest : public Game{
private:
	BaseNode* node;
public:
	QuaternionTest();
	~QuaternionTest();

	void Update(float deltaTime) override;
	void MoveCamera3D(bool rotate = true, bool move = true);

};
#endif 
