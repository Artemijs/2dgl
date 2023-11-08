#ifndef BASE_PANEL_H
#define BASE_PANEL_H
#include "../Util/MemoryManager.h"
#include "../Game/RenderNode.h"
#include <vector>




class BasePanel :public Memory {
private:

	RenderNode* _parent;
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

};

#endif