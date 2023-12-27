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

const float BasePanel::BORDER_INTERSECTION_WIDTH = 3.50f;

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
	_resizing = false;

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
	_resizing = false;

}


void BasePanel::SetMouseCallBacks() {
	
	Mouse* m = Game::GetMouse();
	
	m->AddCallback(0, new std::pair<const unsigned int, mouse_call>(0, [&](const Vec2& mousePos) {
			
			_resizing = true;
			return false; 
		
		}));

	m->AddCallback(1, new std::pair<const unsigned int, mouse_call>(0, [&](const Vec2& mousePos) {
	
			_resizing = false;
			return false;

		}));
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
	if (_pointerAction != 0 && _resizing == true) {
		ResizeBorder();
	}
}


void BasePanel::ResizeBorder() {
	
	Vec3 size = _parent->GetTransform()._scale;
	Vec3 pos = _parent->GetTransform()._position;
	Vec2 mousePos = Game::GetMouse()->GetPosition();


	//1 = left 2 = right 3 = top 4 = bot

	if (_pointerAction == 1) {
		//chnage position of left edge
		float sizeDelta = (pos.x - size.x * 0.5f) - mousePos.x;
		pos.x -= sizeDelta * 0.5;
		size.x += sizeDelta;
		_parent->SetPosition(pos);
		_parent->SetScale(size);
		CalculateCorners(pos, size);

	}
	else if (_pointerAction == 2) {
		//chnage position of right edge
		float sizeDelta = (pos.x + size.x * 0.5f) - mousePos.x;
		pos.x -= sizeDelta * 0.5;
		size.x -= sizeDelta;
		_parent->SetPosition(pos);
		_parent->SetScale(size);
		CalculateCorners(pos, size);

	}
	else if (_pointerAction == 3) {
		//chnage position of top edge
		float sizeDelta = (pos.y + size.y * 0.5f) - mousePos.y;
		pos.y -= sizeDelta * 0.5;
		size.y -= sizeDelta;
		_parent->SetPosition(pos);
		_parent->SetScale(size);
		CalculateCorners(pos, size);
	}
	else if (_pointerAction == 4) {
		//chnage position of bot edge
		float sizeDelta = (pos.y - size.y * 0.5f) - mousePos.y;
		pos.y -= sizeDelta * 0.5;
		size.y += sizeDelta;
		_parent->SetPosition(pos);
		_parent->SetScale(size);
		CalculateCorners(pos, size);
	}
	//				diagonals
	else if (_pointerAction == 5) {
		//chnage position of top left edge
		float sizeDeltaX = (pos.x - size.x * 0.5f) - mousePos.x;
		float sizeDeltaY = (pos.y + size.y * 0.5f) - mousePos.y;
		pos.y -= sizeDeltaY * 0.5;
		size.y -= sizeDeltaY;
		pos.x -= sizeDeltaX * 0.5;
		size.x += sizeDeltaX;
		_parent->SetPosition(pos);
		_parent->SetScale(size);
		CalculateCorners(pos, size);
	}
	else if (_pointerAction == 6) {
		//chnage position of top right edge
		float sizeDeltaX = (pos.x + size.x * 0.5f) - mousePos.x;
		float sizeDeltaY = (pos.y + size.y * 0.5f) - mousePos.y;
		pos.y -= sizeDeltaY * 0.5;
		size.y -= sizeDeltaY;
		pos.x -= sizeDeltaX * 0.5;
		size.x -= sizeDeltaX;
		_parent->SetPosition(pos);
		_parent->SetScale(size);
		CalculateCorners(pos, size);
	}
	else if (_pointerAction == 7) {
		//chnage position of bot left edge
		float sizeDeltaX = (pos.x - size.x * 0.5f) - mousePos.x;
		float sizeDeltaY = (pos.y - size.y * 0.5f) - mousePos.y;
		pos.y -= sizeDeltaY * 0.5;
		size.y += sizeDeltaY;
		pos.x -= sizeDeltaX * 0.5;
		size.x += sizeDeltaX;
		_parent->SetPosition(pos);
		_parent->SetScale(size);
		CalculateCorners(pos, size);
	}
	else if (_pointerAction == 8) {
		//chnage position of bot right edge
		float sizeDeltaX = (pos.x + size.x * 0.5f) - mousePos.x;
		float sizeDeltaY = (pos.y - size.y * 0.5f) - mousePos.y;
		pos.y -= sizeDeltaY * 0.5;
		size.y += sizeDeltaY;
		pos.x -= sizeDeltaX * 0.5;
		size.x -= sizeDeltaX;
		_parent->SetPosition(pos);
		_parent->SetScale(size);
		CalculateCorners(pos, size);
	}
}


void BasePanel::MouseEdgeInterection(const Vec2& mousePos) {
	
	//0: topLeft , 1: topright  , 2: bot rright, 3: bottom left
	
	
	bool noCollision = true;
	bool collisionData[4]{ false, false, false, false };

	Vec2 axis(0, 1);
	Vec2 point = _corners[0];
	float mouseProj = Vec2::Dot(axis, mousePos);
	float pointProj = Vec2::Dot(axis, point);
	
	//top edge
	collisionData[0] = (mouseProj >= pointProj - BORDER_INTERSECTION_WIDTH && mouseProj <= pointProj + BORDER_INTERSECTION_WIDTH);
	
	
	//bottom
	point = _corners[2];
	pointProj = Vec2::Dot(axis, point);
	
	collisionData[1] = (mouseProj >= pointProj - BORDER_INTERSECTION_WIDTH && mouseProj <= pointProj + BORDER_INTERSECTION_WIDTH);

	//left
	axis = Vec2(1, 0);
	point = _corners[0];
	mouseProj = Vec2::Dot(axis, mousePos);
	pointProj = Vec2::Dot(axis, point);

	collisionData[2] = (mouseProj >= pointProj - BORDER_INTERSECTION_WIDTH && mouseProj <= pointProj + BORDER_INTERSECTION_WIDTH);

	
	//right
	point = _corners[1];
	mouseProj = Vec2::Dot(axis, mousePos);
	pointProj = Vec2::Dot(axis, point);

	collisionData[3] = (mouseProj >= pointProj - BORDER_INTERSECTION_WIDTH && mouseProj <= pointProj + BORDER_INTERSECTION_WIDTH);

	
	
	//top
		if (collisionData[0]) {
			//top left
			if (collisionData[2]) {
				Game::GetMouse()->SetCursorImg(3);
				SetPointerAction(5);
				//_pointerAction = 5;
			}
			//top right
			else if (collisionData[3]) {
				Game::GetMouse()->SetCursorImg(3);
				SetPointerAction(6);
				//_pointerAction = 6;
			}
			//just top
			else {
				Game::GetMouse()->SetCursorImg(2);
				SetPointerAction(3);
				//_pointerAction = 3;
			}
		}
		//bot
		else if (collisionData[1]) {
			//bot left
			if (collisionData[2]) {
				Game::GetMouse()->SetCursorImg(3);
				SetPointerAction(7);
				//_pointerAction = 7;
			}
			//bot right
			else if (collisionData[3]) {
				Game::GetMouse()->SetCursorImg(3);
				//_pointerAction = 8;
				SetPointerAction(8);
			}
			//just bot
			else {
				Game::GetMouse()->SetCursorImg(2);
				//_pointerAction = 4;
				SetPointerAction(4);
			}

		}
		//left
		else if (collisionData[2]) {
			Game::GetMouse()->SetCursorImg(1);
			//_pointerAction = 1;
			SetPointerAction(1);
		}
		//right
		else if (collisionData[3]) {
			Game::GetMouse()->SetCursorImg(1);
			//_pointerAction = 2;
			SetPointerAction(2);
		}
	


	if (!_resizing) {
		if (!collisionData[0] && !collisionData[1] && !collisionData[2] && !collisionData[3] && _pointerAction != 0) {
			//_pointerAction = 0;
			SetPointerAction(0);
			Game::GetMouse()->SetCursorImg(0);
		}
	}
}


void BasePanel::SetPointerAction(const unsigned int newAction) {
	/*if( _pointerAction == 0 || _pointerAction >4 || newAction == 0)
		_pointerAction = newAction;*/
	if (_pointerAction == 0 || newAction == 0) {
		//allowed to change everything
		_pointerAction = newAction;
	}
	else if (newAction > 4) {
		_pointerAction = newAction;
	}
}