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
	BasePanel(const char* name, BaseNode* parentOfparent, Vec3 pos, Vec3 size);
	~BasePanel();
	//0: Left , 1: top , 2: rright, 3: bottom
	void AddNeighbour(BasePanel* bp, unsigned int direction);

};

#endif