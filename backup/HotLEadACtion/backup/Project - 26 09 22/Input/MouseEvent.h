#ifndef MOUSE_EVENT_H
#define MOUSE_EVENT_H
#include "../Math/Matrix4x4.h"
#include "../Math/Bounds.h"
class MouseEvent{
protected:
	Bounds* _bounds;

public:
	MouseEvent(Bounds* bounds);
	virtual void OnMouseEnter(const Vec2* mPos) = 0;
	virtual void OnMouseLeave(const Vec2* mPos) = 0;
	//these need to be rewritten 
	virtual void OnPressed(const Vec2* mpos) = 0;
	virtual void OnReleased(const Vec2* mpos) = 0;
	virtual void OnClick(const Vec2* mPos) = 0;

	virtual void OnDoubleClick(const Vec2* mPos) = 0;
	virtual void OnHover(const Vec2* mPos) = 0;
	virtual void OnEndHover(const Vec2* mPos) = 0;
	Bounds* GetBounds() { return _bounds; }

};
#endif
