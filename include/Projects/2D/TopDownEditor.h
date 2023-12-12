#ifndef TOP_DOWN_EDITOR_H
#define TOP_DOWN_EDITOR_H
#include "Game/Game.h"
#include "Util/MemoryManager.h"
#include "Projects/2D/TileMapMaterial.h"
#include "Game/RenderNode.h"
#include "Util/MemoryManager.h"
namespace TDP {
	/*
	struct Tile {

	};
	*/
	/*
		* 
*	ui_panel
*		- dock it
*		- tab it
*		- sclae it 
* 
*	class BasePanel{
*	
* private:

*	std::vector<std::vector<BasePanel*> _neighbours;
*	
* public:
		BasePanel();
		~BasePanel();
		void AddNeighbor(BasePanel* bPane, unsigned int dir){
			//0: Left , 1: top , 2: rright, 3: bottom
			//0 - 2 left to right	(0 + 2) 2 % 3 = 2 
			//1 - 3 top to bottom	(1 + 2) 3 % 4 = 4
			//2 - 1 right to left	(2 + 2) 4 % 4 = 0
			//3 - 2 bottom to top	(3 + 2) 5 % 4 = 1 
			
			//check if neighbour already there ?
			_neighbour->at(dir)->push_back(bPane);
			bPane->addNeighbour(this, (dir + 2)% 4);
			
			if dir == 0 kinda 
				get top or bottom neighbors
		

		}
	};
* 
* 
* 
		if you are dragging a panel and hovering over a collidedWithPanel
			direction = calculate direction to center of collidedWithPanel			
*			if let go of mouse 1
				collidedWithPanel->add neighbor(draggedPanel, direction)
* 
* 
* 
* 
	the top down level editor has to :
		- Select Tile
		- Select texture to paint with
		- Change tile texture byte data to selexcted byte data
		- Save Texture

	*/



	class TopDownEditor : public Game {

	private:
		const unsigned int _widthBTBG;
		const unsigned int _heightBTBG;
		float _tileSize;
		BaseNode* _mainTileMesh;
		BaseNode* _filePanel;
		BaseNode* _detailsPanel;
		TileMapMaterial* _tileMapMat;
		bool _moveOver;
		Vec2Int _currentTile;
		void CreateNew();
		void CreateTopBar();
		void CreateBottomBar();
		void CreateFilePanel();
		void CreateDetailsPanel();

	public:
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
