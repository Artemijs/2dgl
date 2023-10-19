#ifndef TOP_DOWN_EDITOR_H
#define TOP_DOWN_EDITOR_H
#include "../../Game/Game.h"



class TopDownEditor : public Game {

private:
	const unsigned int _widthBTBG;
	const unsigned int _heightBTBG;
	BaseNode* _mainTileMesh;
	void CreateNew();
public :
	TopDownEditor();
	~TopDownEditor();
	
	void Update(float deltaTime) override;
	void MoveCamera();

};
#endif 
