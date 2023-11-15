#include "BasePanel.h"
#include "../Game/Game.h"
#include "../Game/FBOComponent.h"

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



BasePanel::BasePanel() {

	_parent = new RenderNode(Vec3(), Vec3(), 0);
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

BaseNode* BasePanel::GetNode() {
	return _parent;
}