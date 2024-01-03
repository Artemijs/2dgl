#ifndef BASE_PANEL_H
#define BASE_PANEL_H
#include "Util/MemoryManager.h"
#include "Game/RenderNode.h"
#include <vector>
#include "Graphics/Materials/MaterialUiSprite.h"
#include "UI/Button.h"
class RenderNodeMat : public MaterialUiNoTex {
private:
public:
	Vec4 _borderColor;
	float _borderSize;
	Vec2 _textureSize;
	Vec2 _uv_offset;
	Vec2 _uv_scale;
	RenderNodeMat();
	RenderNodeMat(const Shader* s);
	/// <summary>
	/// shaders and textures get deleted in renderer
	/// </summary>
	virtual ~RenderNodeMat();
	void Bind(const Matrix4x4* model) const override;
	void Unbind() const override;
	void RecalcUV(const Transform& t);
};


//									TAB
//-----------------------------------------------------------------------

class Tab {

private:
	const char* _name;
	//parented to basepanel parent node
	Button* _tabUI;
	//parented to base panel data node
	BaseNode* _tabData;

public: 
	Tab();
	Tab(const char* name, BaseNode* data, float tabHeight);
	~Tab();
	void Select();
	void Deselect();
	void Drag(const Vec2& mousePos);

};



//									BASE PANEL
//----------------------------------------------------------------------------




class BasePanel : public Memory {
private:

	
	SList<Tab*>* _tabs;

	unsigned int _pointerAction;
	bool _resizing;
	const static float BORDER_INTERSECTION_WIDTH;
	
	/// <summary>
	/// the render node that ui is parented to
	/// </summary>
	RenderNode* _parent;
	BaseNode* _tabParent;
	BaseNode* _dataParent;
	RenderNodeMat* _panelMaterial;

	const char* _name;
	
	//0: Left , 1: top , 2: rright, 3: bottom
	std::vector<std::vector<BasePanel*>*>* _neighbours;
	
	//0: topLeft , 1: topright  , 2: bot rright, 3: bottom left
	Vec2* _corners;
	
	void MouseEdgeInterection(const Vec2& mousePos);
	void CalculateCorners(const Vec3& pos, const Vec3& size);
	void SetMouseCallBacks();
	void ResizeBorder();
	void SetPointerAction(const unsigned int newAction);
public:
	BasePanel();
	/// <summary>
	/// 
	/// </summary>
	/// <param name="name"></param>
	/// <param name="parentOfparent"></param>
	/// <param name="pos">z value has to be -1</param>
	/// <param name="size"></param>
	BasePanel(const char* name, BaseNode* parentOfparent, Vec3 pos, Vec3 size);
	~BasePanel();
	//0: Left , 1: top , 2: rright, 3: bottom
	void AddNeighbour(BasePanel* bp, unsigned int direction);
	void SetBackgroundColor(const Vec3& col);
	RenderNodeMat* GetMaterial();
	BaseNode* GetParentAsNode();
	RenderNode* GetParentRenderNode();
	void Update(const float deltaTime);
	void AddTab(Tab* tab);

};

#endif