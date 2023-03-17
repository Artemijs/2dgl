#ifndef SPRITE_H
#define SPRITE_H

#include "Graphic.h"

class Sprite : public Graphic{
private:

public :
	Sprite();
	Sprite(const char* path, SpriteData spData);
	~Sprite();
	void BeforeDraw();
	void Draw();
};

#endif // !SPRITE_H
