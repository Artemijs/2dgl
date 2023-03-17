#include "AnimatedSprite.h"
#include <iostream>
#include "Renderer.h"
AnimatedSprite::AnimatedSprite():
	Sprite(),
	_texScale(Vec2()),
	_looping(false),
	_currentFrame(0),
	_startEndFrames(Vec2Int(0,1)),
	_maxXYFrames(Vec2Int(1,1)),
	_timePerFrame(0),
	_currentTime(0){
	_shader = Renderer::instance()->GetShader(1);
	_on = true;
}
AnimatedSprite::~AnimatedSprite() {}
AnimatedSprite::AnimatedSprite(const char* path, SpriteData rect) :
	Sprite(path, rect),
	_texScale(Vec2()),
	_looping(false),
	_currentFrame(0),
	_startEndFrames(Vec2Int(0, 1)),
	_maxXYFrames(Vec2Int(1, 1)),
	_timePerFrame(0),
	_currentTime(0) {
	_shader = Renderer::instance()->GetShader(1);
	_on = true;
}
void AnimatedSprite::SetAnimationData(int startFrame, int length, int maxXframes, int maxYframes, float timePerFrame, bool looping) {
	_texScale.x = 1.0f / maxXframes;
	_texScale.y = 1.0f / maxYframes;
	_timePerFrame = timePerFrame;
	_maxXYFrames.x = maxXframes;
	_maxXYFrames.y = maxYframes;
	_startEndFrames.x = startFrame;
	_startEndFrames.y = startFrame + length;
	_uvOffset.x = _currentFrame % _maxXYFrames.x;
	_uvOffset.y = _currentFrame / _maxXYFrames.y;
	_currentFrame = startFrame;
	_looping = looping;
}
void AnimatedSprite::Update(float deltaTime) {
	if (!_on) return;
	_currentTime += deltaTime;
	if (_currentTime >= _timePerFrame) {
		_currentFrame++;
		if (_currentFrame >= (_startEndFrames.x + _startEndFrames.y) ) {
			
			if (!_looping) {
				_on = false;
				_currentFrame = _startEndFrames.y;
				return;
			}
			else {
				_currentFrame = _startEndFrames.x;
			}
		}
		
		
		_uvOffset.y = _currentFrame / _maxXYFrames.x;
		_uvOffset.x = _currentFrame - (_uvOffset.y * _maxXYFrames.x);
		_currentTime = 0;
	}
}
void AnimatedSprite::BeforeDraw() {
	Sprite::BeforeDraw();
	int uvOffId = glGetUniformLocation(_shader->ID, "uvOff");
	glUniform2f(uvOffId, _uvOffset.x, _uvOffset.y);
	int scaleId = glGetUniformLocation(_shader->ID, "scale");
	glUniform2f(scaleId, _texScale.x, _texScale.y);

}