#ifndef SPRITE_H
#define SPRITE_H

#include "Graphic.h"

	class Sprite : public Graphic {
	private:

	public:
		Sprite();
		Sprite(const char* path);
		~Sprite();
		void Bind(Matrix4x4* model) const;
	};



#endif // !SPRITE_H
