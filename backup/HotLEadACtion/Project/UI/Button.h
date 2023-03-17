#ifndef BUTTON_H
#define BUTTON_H
#include "UISprite.h"
#include "../Graphics/Text.h"
#include "../Input/MouseEvent.h"

class Button: public UIsprite, public MouseEvent{
private :
	Text* _txt;
	Vec2 _texScale;
	Vec2 _uvOffset;
	int _pressedSound;
	int _releasedSfx;
	int _enterSfx;
	//void CalculateUVs();
public  :
	Button();
	Button(const char* txt, Vec3 pos, Vec3 size, float ang);
	~Button();
	void BeforeDraw();
	void Draw();
	/*void UpdateMatrix(Matrix4x4 parent);
	Vec3 GetPosition();
	void SetPosition(const Vec3* pos);*/
	void OnMouseEnter(const Vec2* mPos);
	void OnMouseLeave(const Vec2* mPos);
	void OnClick(const Vec2* mPos);
	void OnDoubleClick(const Vec2* mPos);
	void OnHover(const Vec2* mPos);
	void OnEndHover(const Vec2* mPos);
	void OnPressed(const Vec2* mPos);
	void OnReleased(const Vec2* mPos);
};

#endif // !BUTTON_H
