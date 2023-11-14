#ifndef BASEPANELTEST_H
#define BASEPANELTEST_H
#include"../../../Game/Game.h"
#include "../../../UI/BasePanel.h"
#include "../../../Graphics/Renderer.h"


class BasePanelTest : public Game {
private:
	/*BasePanel* _topPanel;
	BasePanel* _mainPanel;
	BasePanel* _botPanel;*/
	Renderer* _r;
public :
	BasePanelTest();
	~BasePanelTest();
	void Update(float deltaTime) override;
	void MoveCamera3D(bool rotate = true, bool move = true);
	void CreatePanels();
	

};
#endif

