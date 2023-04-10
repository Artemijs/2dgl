#ifndef UISLIDER_H
#define UISLIDER_H

#include "../Graphics/Sprite.h"
#include "Element.h"
#include "Button.h"
namespace v1_5 {
	class SliderPin;

	class UISlider : public Sprite {
	private:
		bool _vertical;
		//UIsprite* _pin;
		Button* _pin;
		float _position;

	public:
		UISlider();
		UISlider(Vec3 pos, Vec3 size, float ang, bool vertical = true);
		UISlider(const char* bgPah, const char* pinPath, Vec3 pos, Vec3 size, float ang, bool vertical = true);
		~UISlider();
		void BeforeDraw();
		//void Draw();
		void UpdateModelMatrix(Matrix4x4 parent);
	};


	class SliderPin : public Button {
	private:
		Matrix4x4 _originOffset;
	public:
		SliderPin(const char* txt, Vec3 pos, Vec3 size, float ang);
		//~SliderPin();
		void SetOriginOffset(Matrix4x4 offset);
		void BeforeDraw();
		void Draw();
		void OnMouseEnter(const Vec2* mPos);
		void OnMouseLeave(const Vec2* mPos);
		void OnClick(const Vec2* mPos);
		void OnDoubleClick(const Vec2* mPos);
		void OnHover(const Vec2* mPos);
		void OnEndHover(const Vec2* mPos);
		void OnPressed(const Vec2* mPos);
		void OnReleased(const Vec2* mPos);

	};
}
#endif