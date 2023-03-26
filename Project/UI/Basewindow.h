#ifndef BASE_WINDOW_H
#define BASE_WINDOW_H
#include "../Graphics/Sprite.h"
#include "../Input/MouseEvent.h"
#include "../Game/Game.h"
class BaseWindow : public Sprite, public MouseEvent {
private:
	Vec2 _prevMouse;
	bool _dragging;
public :
	BaseWindow();
	//path to the source of the background image
	BaseWindow(const char* path, Vec3 pos, Vec3 size, float ang, BaseObject* parent = NULL);
	//uses default image as background
	BaseWindow(Vec3 pos, Vec3 size, float ang, BaseObject* parent = NULL);

	void Update(float deltaTime);

	void OnMouseEnter(const Vec2* mPos);
	void OnMouseLeave(const Vec2* mPos);
	//these need to be rewritten 
	void OnPressed(const Vec2* mpos);
	void OnReleased(const Vec2* mpos);
	void OnClick(const Vec2* mPos);

	void OnDoubleClick(const Vec2* mPos);
	void OnHover(const Vec2* mPos);
	void OnEndHover(const Vec2* mPos);
};
#endif // !BASE_WINDOW_H
