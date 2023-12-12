#ifndef UI_HANDLER_H
#define UI_HANDLER_H
#include "UI/BasePanel.h"
#include <vector>




class UIHandler {

private:
	static std::vector<BasePanel*>* _panels;

public :
	static BasePanel* GetPanel(const char* name, BaseNode* parent, Vec3 pos, Vec3 size);
	static void Clean();
	/// <summary>
	/// handle Mouse Events like resizing and moving tabs
	/// </summary>
	/// <param name="deltaTime"></param>
	static void Update(const float deltaTime);


};
#endif // !UI_HANDLER_H
