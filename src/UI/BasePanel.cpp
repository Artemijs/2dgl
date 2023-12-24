#include "UI/BasePanel.h"
#include "Game/Game.h"
#include "Game/FBOComponent.h"

/*



	EDGE BORDER OUTLINE THICKNESS SHADER
	POINT LINE COLLISION
	CHANGE CURSOR IMAGE
	CREATE A NEW PANEL
	TABS
	SELECT TABS
	MOVE TABS
	CLOSE TABS
	MOVE TABS TO DIFFERENT PANELS
	DOCK TABS INTO NEW PANELS



*/


RenderNodeMat::RenderNodeMat() {

}


RenderNodeMat::RenderNodeMat(const Shader* s) : MaterialUiNoTex(s){

}


/// <summary>
/// shaders and textures get deleted in renderer
/// </summary>
RenderNodeMat::~RenderNodeMat() {

}





void RenderNodeMat::Bind(const Matrix4x4* model) const {
	MaterialUiNoTex::Bind(model);

	glUniform4f(glGetUniformLocation(_shader->ID,"borderColor"), _borderColor.x, _borderColor.y, _borderColor.z, _borderColor.a);
	glUniform2f(glGetUniformLocation(_shader->ID, "size"), _textureSize.x, _textureSize.y);
	glUniform1f(glGetUniformLocation(_shader->ID, "borderSize"), _borderSize);
}


void RenderNodeMat::Unbind() const {
	MaterialUiNoTex::Unbind();

}




//										BASE PANEL
//----------------------------------------------------------------------------------------

const float BasePanel::BORDER_INTERSECTION_WIDTH = 2.50f;

BasePanel::BasePanel() {

	_parent = new RenderNode(Vec3(100, 100, -1), Vec3(100, 100, 1), 0);
	Game::_world->AddChild(_parent);

	_neighbours = new std::vector<std::vector<BasePanel*>*>{
		new std::vector<BasePanel*>(),		//left
		new std::vector<BasePanel*>(),		//top
		new std::vector<BasePanel*>(),		//right
		new std::vector<BasePanel*>(),		//bot
	};
	_name = "Empty";
	//MemoryManager::CacheGarbage(this);
	_panelMaterial = dynamic_cast<RenderNodeMat*> (_parent->GetMaterial());
	_panelMaterial->_borderColor = Vec4(0.1f, 0.1f, 0.1f, 1.0f);
	_panelMaterial->_borderSize = 1.0f;
	CalculateCorners(Vec3(100, 100, -1), Vec3(100, 100, 1));
	_pointerAction = 0;
}


BasePanel::BasePanel(const char* name, BaseNode* parentOfparent, Vec3 pos, Vec3 size) {

	_parent = new RenderNode(pos, size, 0);
	parentOfparent->AddChild(_parent);
	_neighbours = new std::vector<std::vector<BasePanel*>*>{
		new std::vector<BasePanel*>(),//left
		new std::vector<BasePanel*>(),//top
		new std::vector<BasePanel*>(),//right
		new std::vector<BasePanel*>(),//bot
	};
	_name = name;
	//MemoryManager::CacheGarbage(this);
	_panelMaterial = dynamic_cast<RenderNodeMat*> (_parent->GetMaterial());
	_panelMaterial->_borderColor = Vec4(0.5f, 0.5f, 0.5f, 1.0f);
	_panelMaterial->_borderSize = 2.0f;
	CalculateCorners(pos, size);
	SetMouseCallBacks();
	_pointerAction = 0;

}


void BasePanel::SetMouseCallBacks() {
	
	Mouse* m = Game::GetMouse();
	
	m->AddCallback(0, new std::pair<const unsigned int, mouse_call>(0, [&](const Vec2& mousePos) {
		std::cout << "HELLO FROM MOUSE CALLBACK ONLY ONCE \n";
		return true; }));
	/*m->AddCallback(0, std::pair<const unsigned int, mouse_call>(0, [&](const Vec2& mousePos) {
		std::cout << "HELLO FROM MOUSE CALLBACK EVERY TIME\n";
		return false; }));
	m->AddCallback(0, std::pair<const unsigned int, mouse_call>(1, [&](const Vec2& mousePos) {
		std::cout << "HELLO FROM MOUSE CALLBACK DIFFERENT BUTTON\n";
		return false; }));*/
}


void BasePanel::CalculateCorners(const Vec3& pos, const Vec3& size) {
	
	_corners = new Vec2[4];

	//0: topLeft , 1: topright  , 2: bot rright, 3: bottom left
	//origin bottom left
	
	//top left
	_corners[0] = Vec2(pos.x - size.x * 0.5f, pos.y + size.y * 0.5f);
	
	//top right
	_corners[1] = Vec2(pos.x + size.x * 0.5f, pos.y + size.y * 0.5f);

	//bot rigth
	_corners[2] = Vec2(pos.x + size.x * 0.5f, pos.y - size.y * 0.5f);

	//bot left
	_corners[3] = Vec2(pos.x - size.x * 0.5f, pos.y - size.y * 0.5f);
}

/// <summary>
/// all panels are deleted by MemoryManager
/// </summary>
BasePanel::~BasePanel() {
	//Render node is deleted by delete world call
	//neighbors are deleted by Memory manager
	//delete the containers that store neighbors
	for (int i = 0; i < _neighbours->size(); i++) {
		delete _neighbours->at(i);
	}
	delete _neighbours;
	printf("deleting PANELS %s \n", _name);
	delete[] _corners;

}


void BasePanel::AddNeighbour(BasePanel* bp, unsigned int direction) {
	if (direction > 3) {
		printf("ADDING NEIGHBOUR ERROR in baesepanel\n");
		return;
	}
	_neighbours->at(direction)->push_back(bp);

}


void BasePanel::SetBackgroundColor(const Vec3& col) {
	
	_parent->GetComponent<FBOComponent>()->SetClearColor(col);
}


RenderNodeMat* BasePanel::GetMaterial() {
	return _panelMaterial;

}

BaseNode* BasePanel::GetParentAsNode() {
	return _parent;
}


RenderNode* BasePanel::GetParentRenderNode() {
	return _parent;
}


void BasePanel::Update(const float deltaTime) {
	MouseEdgeInterection(Game::GetMouse()->GetPosition());
}


void BasePanel::MouseEdgeInterection(const Vec2& mousePos) {
	
	//0: topLeft , 1: topright  , 2: bot rright, 3: bottom left
	
	//top edge

	Vec2 axis(0, 1);
	Vec2 point = _corners[0];
	float mouseProj = Vec2::Dot(axis, mousePos);
	float pointProj = Vec2::Dot(axis, point);
	bool noCollision = true;
	if (mouseProj >= pointProj - BORDER_INTERSECTION_WIDTH && mouseProj <= pointProj + BORDER_INTERSECTION_WIDTH) {
		std::cout << "COllided with TOP edge\n";
		Game::GetMouse()->SetCursorImg(2);
		_pointerAction = 2;
		noCollision = false;
	}
	//bottom
	point = _corners[2];
	pointProj = Vec2::Dot(axis, point);
	if (mouseProj >= pointProj - BORDER_INTERSECTION_WIDTH && mouseProj <= pointProj + BORDER_INTERSECTION_WIDTH) {
		std::cout << "COllided with BOT edge\n";
		Game::GetMouse()->SetCursorImg(2);
		_pointerAction = 2;
		noCollision = false;
	}
	//left
	axis = Vec2(1, 0);
	point = _corners[0];
	mouseProj = Vec2::Dot(axis, mousePos);
	pointProj = Vec2::Dot(axis, point);
	if (mouseProj >= pointProj - BORDER_INTERSECTION_WIDTH && mouseProj <= pointProj + BORDER_INTERSECTION_WIDTH) {
		std::cout << "COllided with LEFT edge\n";
		Game::GetMouse()->SetCursorImg(1);
		_pointerAction = 1;
		noCollision = false;
	}
	//right
	point = _corners[2];
	mouseProj = Vec2::Dot(axis, mousePos);
	pointProj = Vec2::Dot(axis, point);
	if (mouseProj >= pointProj - BORDER_INTERSECTION_WIDTH && mouseProj <= pointProj + BORDER_INTERSECTION_WIDTH) {
		std::cout << "COllided with RIGHT edge\n";
		Game::GetMouse()->SetCursorImg(1);
		_pointerAction = 1;
		noCollision = false;
	}
	

	if (noCollision && _pointerAction != 0) {
		_pointerAction = 0;
		Game::GetMouse()->SetCursorImg(0);
	}
}