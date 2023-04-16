#ifndef SPRITE_H
#define SPRITE_H

#include "Graphic.h"

	class Sprite : public Graphic {
	private:
		static const unsigned int _id;
	public:
		Sprite();
		Sprite(const char* path);
		~Sprite();
		void Bind(Matrix4x4* model) const;
		const unsigned int ID();
	};



#endif // !SPRITE_H
