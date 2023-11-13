#ifndef BASE_PANEL_H
#define BASE_PANEL_H
#include "../Util/MemoryManager.h"
#include "../Game/RenderNode.h"
#include <vector>
#include "../Graphics/Materials/MaterialUiSprite.h"

class RenderNodeMat : public MaterialUiNoTex {
private:
public:
	Vec4 _borderColor;
	float _borderSize;
	Vec2 _textureSize;
	RenderNodeMat();
	RenderNodeMat(const Shader* s);
	/// <summary>
	/// shaders and textures get deleted in renderer
	/// </summary>
	virtual ~RenderNodeMat();
	void Bind(const Matrix4x4* model) const override;
	void Unbind() const override;
};

class BasePanel : public Memory {
private:

	RenderNode* _parent;
	RenderNodeMat* _panelMaterial;
	const char* _name;
	//0: Left , 1: top , 2: rright, 3: bottom
	std::vector<std::vector<BasePanel*>*>* _neighbours;
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

};

#endif