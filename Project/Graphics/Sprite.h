#ifndef SPRITE_H
#define SPRITE_H

#include "Graphic.h"
#include "./Materials/MaterialUISprite.h"
class Sprite : public Graphic {
private:
		
public:
	static const unsigned int _component_id;

	/// <summary>
	/// default material constructor uses a UI shader which has to have basenode position z to be -1
	/// </summary>
	Sprite();
	Sprite(const char* path);
	Sprite( BaseMaterial* m);
	~Sprite();
	const unsigned int ID() const override;
};



#endif // !SPRITE_H
