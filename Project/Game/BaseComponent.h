#ifndef BASECOMPONENT_H
#define BASECOMPONENT_H
#include <vector>
	
class BaseComponent{
protected:
	const bool _isGraphic;
public :
	BaseComponent();
	virtual ~BaseComponent();
	virtual const unsigned int ID() const = 0;
	const bool IsGraphic();
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