#include "UISlider.h"

UISlider::UISlider() : UIsprite( "Assets/Textures/sliderBGdefault.png", Vec3(), Vec3(), 0), _vertical(false) {
	
	//_pin = new Button("Assets/Textures/btn.png", Vec3(), Vec3(), 0);
	_position = 0;
}


UISlider::UISlider(Vec3 pos, Vec3 size, float ang, bool vertical) : UIsprite("Assets/Textures/sliderBGdefault.png", pos, size, ang) , _vertical(vertical) {
	//SpriteData pinRect = rect;
	//pinRect._size.y = pinRect._size.y * 0.1f;
	//pinRect._position = Vec3(0, 0, pinRect._position.z + 0.1f);
	_pin = new Button(".", Vec3(0, 0, -1), Vec3(25, 25, 1), 0);
	
	AddChild(_pin);
	_position = 0;
}


UISlider::UISlider(const char* bgPah, const char* pinPath, Vec3 pos, Vec3 size, float ang, bool vertical): UIsprite(bgPah, pos, size, ang), _vertical(vertical) {
	//SpriteData pinRect = rect;
	//rect._size = Vec2(10, 10);
	//pinRect._position = Vec3(0, 0, rect._position.z + 0.01f);
	//_pin = new Button(pinPath, Vec3(100, 100, -1), Vec3(20,20, 1), 0);
	//_children->push_back(_pin);
	_position = 0;
}

UISlider::~UISlider() {
	delete _pin;
	//delete _children->at(0);
}


void UISlider::BeforeDraw() {
	//will this call Graphic::BeforeDraw()?
	UIsprite::BeforeDraw();
}

/*void UISlider::Draw() {
	
}*/
void UISlider::UpdateModelMatrix(Matrix4x4 parent) {
	//UIsprite::UpdateTransform(parent);
	//_pin->UpdateModelMatrix(parent);
	/*float z = _rect._position.z;
	_rect._position.z = 0;
	_model = Matrix4x4::TranslationMatrix(_rect._position) * parent;
	_rect._position.z = z;
	_model.buff[11] = z;
	_model = _model * Matrix4x4::RotationMatrix(_rect._angle)
		* Matrix4x4::ScaleMatrix(Vec3(_rect._size.x, _rect._size.y, 1));*/
}


SliderPin::SliderPin(const char* txt, Vec3 pos, Vec3 size, float ang) : Button(txt, pos, size, ang){
	
}
void SliderPin::SetOriginOffset(Matrix4x4 offset) {
	_originOffset = offset;
}
void SliderPin::BeforeDraw() {
	Matrix4x4 m = _transform;
	_transform = _transform * _originOffset;
	Button::BeforeDraw();
	_transform = m;
}
void SliderPin::Draw() {
	Button::Draw();
}
void SliderPin::OnMouseEnter(const Vec2* mPos) {
	Button::OnMouseEnter(mPos);
}
void SliderPin::OnMouseLeave(const Vec2* mPos) {
	Button::OnMouseLeave(mPos);
}
void SliderPin::OnClick(const Vec2* mPos) {
	Button::OnClick(mPos);
}
void SliderPin::OnDoubleClick(const Vec2* mPos) {
	Button::OnDoubleClick(mPos);
}
void SliderPin::OnHover(const Vec2* mPos) {
	Button::OnHover(mPos);
}
void SliderPin::OnEndHover(const Vec2* mPos) {
	Button::OnEndHover(mPos);
}
void SliderPin::OnPressed(const Vec2* mPos) {
	Button::OnPressed(mPos);
}
void SliderPin::OnReleased(const Vec2* mPos) {
	Button::OnReleased(mPos);
}