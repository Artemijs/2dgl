#ifndef SPRITE_H
#define SPRITE_H

#include "Graphic.h"
namespace v1_5 {
	class Sprite : public Graphic {
	private:

	public:
		Sprite();
		Sprite(const char* path, Vec3 pos, Vec3 size, float ang, BaseObject* parent);
		~Sprite();
		void BeforeDraw();
		void Draw();
	};
}
namespace v1_6 {
	class Sprite : public Graphic {
	private:

	public:
		Sprite();
		Sprite(const char* path);
		~Sprite();
		void Bind(Matrix4x4* model) const;
	};

};

#endif // !SPRITE_H
