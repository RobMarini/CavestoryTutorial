#include "graphics.h"
#include "animatedSprite.h"
#include <string>
#include "sprite.h"

AnimatedSprite::AnimatedSprite(){}

AnimatedSprite::AnimatedSprite(Graphics &graphics, const std::string &filepath, int sourceX, int sourceY, int width, int height, int positionX, int positionY, int timeToUpdate) :
	Sprite(graphics, filepath, sourceX, sourceY, width, height, positionX, positionY),
	_frameIndex(0),
	_timeElapsed(0),
	_timeToUpdate(timeToUpdate),
	_visible(true),
	_currentAnimationOnce(false),
	_currentAnimation("")
		{}

AnimatedSprite::~AnimatedSprite(){}

void AnimatedSprite::addAnimation(int frames, int x, int y, std::string name, int width, int height, Vector2 offset){
	std::vector<SDL_Rect> rects;
	for (int i = 0; i < frames; i++){
		SDL_Rect newRect = {(i+x)*width,y,width,height};
		rects.push_back(newRect);
	}
	_animations.insert(std::pair < std::string, std::vector<SDL_Rect>>(name, rects));
	_offsets.insert(std::pair < std::string, Vector2>(name, offset));
}

void AnimatedSprite::resetAnimations(){ _animations.clear(); _offsets.clear(); }
void AnimatedSprite::playAnimation(std::string animation, bool once){
	_currentAnimationOnce = once;
	if (_currentAnimation != animation){
		_currentAnimation = animation;
		_frameIndex = 0;
	}
}

void AnimatedSprite::setVisible(bool isVisible){ _visible = isVisible; }

void AnimatedSprite::stopAnimation(){ _frameIndex = 0; animationDone(_currentAnimation); }

void AnimatedSprite::update(int elapsedTime){
	Sprite::update();
	_timeElapsed += elapsedTime;
	if (_timeElapsed > _timeToUpdate){
		//go to next frame
		_timeElapsed -= _timeToUpdate;
		if (_frameIndex < _animations[_currentAnimation].size() - 1){
			_frameIndex++;
		}
		else if (_currentAnimationOnce){
			setVisible(false);
			animationDone(_currentAnimation);
			_frameIndex = 0;
		}
		else{
			_frameIndex = 0;
		}
	}
}

void AnimatedSprite::draw(Graphics &graphics, int x, int y){
	if (_visible){
		SDL_Rect destinationRect;
		destinationRect.x = x + _offsets[_currentAnimation].x;
		destinationRect.y = y + _offsets[_currentAnimation].y;
		destinationRect.w = this->_sourceRect.w * globals::SPRITE_SCALE;
		destinationRect.h = _sourceRect.h * globals::SPRITE_SCALE;

		SDL_Rect sourceRect = _animations[_currentAnimation][_frameIndex];
		graphics.blitSurface(_spriteSheet, &sourceRect, &destinationRect);
	}
}
