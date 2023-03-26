#ifndef ANIMATED_SPRITE_H
#define ANIMATED_SPRITE_H
#include "Sprite.h"

class AnimatedSprite : public Sprite {
private:
	Vec2 _texScale;
	Vec2 _uvOffset;
	bool _looping;
	int _currentFrame;
	Vec2Int _startEndFrames;
	Vec2Int _maxXYFrames;
	float _timePerFrame;
	float _currentTime;
	bool _on;
public:
	AnimatedSprite();
	~AnimatedSprite();
	AnimatedSprite(const char* path, Vec3 pos, Vec3 size, float ang, BaseObject* parent);
	void SetAnimationData(int startFrame, int length, int maxXframes, int maxYframes, float timePerFrame, bool looping);
	void Update(float deltaTime);
	void BeforeDraw();
};

#endif // !ANIMATED_SPRITE_H
