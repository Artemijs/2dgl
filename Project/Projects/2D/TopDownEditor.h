#ifndef TOP_DOWN_EDITOR_H
#define TOP_DOWN_EDITOR_H
#include "../../Game/Game.h"
#include "../../Util/MemoryManager.h"



class TopDownEditor : public Game {

private:
	const unsigned int _widthBTBG;
	const unsigned int _heightBTBG;
	float _tileSize;
	BaseNode* _mainTileMesh;
	void CreateNew();
public :
	TopDownEditor();
	~TopDownEditor();
	
	void Update(float deltaTime) override;
	void MoveCamera3D(bool rotate = true, bool move = true);
	void MoveCamera2D();

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
