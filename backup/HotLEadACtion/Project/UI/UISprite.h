#ifndef UISPRITE_H
#define UISPRITE_H

#include "../Graphics/Graphic.h"
#include "Element.h"
class UIsprite: public Graphic , public Element{
private:

public:
	UIsprite();
	UIsprite(const char* path, Vec3 pos, Vec3 size, float ang);
	~UIsprite();
	void BeforeDraw();
	void Draw();
	void UpdateTransform(Matrix4x4 parent);
	Matrix4x4 GetTransform();
};
#endif