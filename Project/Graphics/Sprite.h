#ifndef SPRITE_H
#define SPRITE_H

#include "Graphic.h"
#include "MaterialDefault.h"
	class Sprite : public Graphic {
	private:
		const MaterialDefault* _material;
	public:
		static const unsigned int _component_id;
		Sprite();
		Sprite(const char* path);
		~Sprite();
		const unsigned int ID() const override;
	};



#endif // !SPRITE_H
