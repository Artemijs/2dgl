#ifndef SPRITE_H
#define SPRITE_H

#include "Graphic.h"
#include "./Materials/MaterialUISprite.h"
class Sprite : public Graphic {
private:
		
public:
	static const unsigned int _component_id;
	Sprite();
	Sprite(const char* path);
	Sprite( BaseMaterial* m);
	~Sprite();
	const unsigned int ID() const override;
};



#endif // !SPRITE_H
