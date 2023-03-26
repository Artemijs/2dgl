#ifndef SPRITE_H
#define SPRITE_H

#include "Graphic.h"

class Sprite : public Graphic{
private:

public :
	Sprite();
	Sprite(const char* path, Vec3 pos, Vec3 size, float ang, BaseObject* parent);
	~Sprite();
	void BeforeDraw();
	void Draw();
};

#endif // !SPRITE_H
