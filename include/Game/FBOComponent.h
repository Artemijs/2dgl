#ifndef FBOCOMPONENT_H
#define FBOCOMPONENT_H
#include <vector>
#include "glad/glad.h"
#include "BaseComponent.h"
#include "Math/Matrix4x4.h"
class FBOComponent: public BaseComponent{
private:
	
	unsigned int _rbo;
	Vec3 _clearColor;
public :
	static const unsigned int _component_id;
	//frame buffer id
	unsigned int _fbo;
	//frame buffer texture id
	unsigned int _fboTexture;
	FBOComponent();
	FBOComponent(const unsigned int width, const unsigned int height);
	~FBOComponent();
	const unsigned int ID() const override;
	void Clear()const;
	void SetClearColor(Vec3 col);
	void SetTextSize(const unsigned int width, const unsigned int height);
};

#endif
/*
class Bounds {
	public :
		virtual bool CheckInside(Vec3 pos) = 0;
		virtual float GetZ() = 0;
		virtual void Translate2World(Matrix4x4 model) = 0;
};

class BoxBounds : public Bounds{
private:
	//0 : top left, 1 : top right, 2 : bot left, 3: botright
	Vec3 _localRect[4];
	Vec3 _worldRect[4];
	//Vec3 _topLeft, _topRight, _botLeft, _botRight;
	//Vec3 _topLeft, _topRight, _botLeft, _botRight;
public:
	BoxBounds();
	BoxBounds(Vec3 topLeft, Vec3 topRight, Vec3 botLeft, Vec3 botRight);
	bool CheckInside(Vec3 pos);
	float GetZ();
	void Translate2World(Matrix4x4 model);
};
	
*/