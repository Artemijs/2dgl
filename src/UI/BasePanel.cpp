#include "UI/BasePanel.h"
#include "Game/Game.h"
#include "Game/FBOComponent.h"
#include "Graphics/Renderer.h"
#include "UI/Button.h"

/*



	EDGE BORDER OUTLINE THICKNESS SHADER
	POINT LINE COLLISION
	CHANGE CURSOR IMAGE

	TABS
	SELECT TABS
	MOVE TABS
	CLOSE TABS

	CREATE A NEW PANEL
	
	
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
	glUniform2f(glGetUniformLocation(_shader->ID, "uv_offset"), _uv_offset.x, _uv_offset.y);
	glUniform2f(glGetUniformLocation(_shader->ID, "uv_scale"), _uv_scale.x, _uv_scale.y);
	glUniform1f(glGetUniformLocation(_shader->ID, "borderSize"), _borderSize);
}


void RenderNodeMat::Unbind() const {
	MaterialUiNoTex::Unbind();

}


void RenderNodeMat::RecalcUV(const Transform& t) {
	Renderer* r = Renderer::instance();
	_uv_scale = Vec2(t._scale.x / r->GetWindowSize().x, t._scale.y / r->GetWindowSize().y);
	Vec2 botLeft = Vec2(t._position.x - t._scale.x * 0.5f, t._position.y - t._scale.y * 0.5f);
	_uv_offset = Vec2(botLeft.x/ r->GetWindowSize().x, botLeft.y/ r->GetWindowSize().y);

}




//									TAB
//-----------------------------------------------------------------------


Tab::Tab() {

}


Tab::Tab(const char* name, BaseNode* data, float tabHeight) :
	_name(name), 
	_tabData(data), 
	_tabUI( new Button(name, Vec3(0,0,0), Vec3(0, tabHeight, 0), 0)){
	_tabUI->ResizeToFitText(0);
}


//nothing to delete, the buton node and data node are deleted by tree destructor
Tab::~Tab() {
	


}


void Tab::Select() {}


void Tab::Deselect() {}


void Tab::Drag(const Vec2& mousePos) {}




//										BASE PANEL
//----------------------------------------------------------------------------------------

const float BasePanel::BORDER_INTERSECTION_WIDTH = 3.50f;

BasePanel::BasePanel() {

	_tabs = new SList<Tab*>();

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
	_panelMaterial->_borderSize = BORDER_INTERSECTION_WIDTH;
	CalculateCorners(Vec3(100, 100, -1), Vec3(100, 100, 1));
	_pointerAction = 0;
	_resizing = false;

}


BasePanel::BasePanel(const char* name, BaseNode* parentOfparent, Vec3 pos, Vec3 size) {

	_parent = new RenderNode(pos, size, 0);
	parentOfparent->AddChild(_parent);

	_tabs = new SList<Tab*>();

	_tabParent = new BaseNode(Vec3(0.0f, size.y * 0.475f, 0.0f), Vec3(1.0f, 0.05f, 1.0f), 0);
	_dataParent = new BaseNode(Vec3(0.0f, size.y * -0.025f, 0.0f), Vec3(1.0f, 0.95f, 1.0f), 0);
	_tabParent->SetInheritTransform(true, true, false);
	_dataParent->SetInheritTransform(true, true, false);
	_parent->AddChild(_tabParent);
	_parent->AddChild(_dataParent);

	_tabParent->AddComponent<Sprite>(new Sprite(new MaterialUiNoTex()));
	_dataParent->AddComponent<Sprite>(new Sprite(new MaterialUiNoTex()));
	_tabParent->GetComponent<Sprite>()->GetMaterial()->_color = Vec4(0.67f, 0.5f, 0.5f, 1.0f);
	_dataParent->GetComponent<Sprite>()->GetMaterial()->_color = Vec4(0.37f, 0.05f, 0.25f, 1.0f);
	
	_neighbours = new std::vector<std::vector<BasePanel*>*>{
		new std::vector<BasePanel*>(),//left
		new std::vector<BasePanel*>(),//top
		new std::vector<BasePanel*>(),//right
		new std::vector<BasePanel*>(),//bot
	};
	_name = name;
	//MemoryManager::CacheGarbage(this);
	_panelMaterial = dynamic_cast<RenderNodeMat*> (_parent->GetMaterial());
	_panelMaterial->_borderColor = Vec4(245.0f/255.0f, 233.0f/255.0f, 66.0f/255.0f, 1.0f);//Vec4(0.5f, 0.5f, 0.5f, 1.0f);
	_panelMaterial->_borderSize = BORDER_INTERSECTION_WIDTH;
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
	delete _tabs;

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

	_panelMaterial->RecalcUV(_parent->GetTransform());
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


void BasePanel::AddTab(Tab* tab) {
	
	_tabs->Add(tab);

}

/*
	TABS 
	What are they, who do they think they are lining up so neatly at the top of a window. 
	What do they do and what motivates them in the morning to do that which they do. Do they ever stop to think what would the world look like if tabs simply didnt tab? If they decided to take a dtour at st peters st, went straght to a pug and had a nice cold one.
	
	Square, 
	Have letters in them, names if you will,
	they can be moved,
	closed and
	clicked on.

	tab area at the top of the base panel
	outline to be below the tab area
	a tab list
	current tab
	
	tab is a :
		mouse on hover:
			
			show close button, highlight
			
			click :
				hide current page
				show page
				change tab color to selected
				change previously selected tab color to idle
			
			click and drag:
					ILL COME BAC TO THIS
							

			close button click:
				remove tab
				select next tab
				hide old page contents
				show new page contents




*/