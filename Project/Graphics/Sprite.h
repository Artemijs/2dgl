#ifndef SPRITE_H
#define SPRITE_H

#include "Graphic.h"

	class Sprite : public Graphic {
	private:
		
	public:
		static const unsigned int _id;
		Sprite();
		Sprite(const char* path);
		~Sprite();
		void Bind(const Matrix4x4* model) const;
		const unsigned int ID() const override;
	};



#endif // !SPRITE_H
