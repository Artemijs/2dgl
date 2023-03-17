#ifndef UIANIMATED_SPRITE_H
#define UIANIMATED_SPRITE_H
#include "UISprite.h"

class UIAnimatedSprite : public UIsprite {
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
	UIAnimatedSprite();
	~UIAnimatedSprite();
	UIAnimatedSprite(const char* path, Vec3 pos, Vec3 size, float ang);
	void SetAnimationData(int startFrame, int length, int maxXframes, int maxYframes, float timePerFrame, bool looping);
	void Update(float deltaTime);
	void BeforeDraw();
};

#endif // !ANIMATED_SPRITE_H
