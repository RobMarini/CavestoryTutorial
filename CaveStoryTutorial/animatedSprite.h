#ifndef ANIMATED_SPRITE_H
#define ANIMATED_SPRITE_H
class Graphics;

#include <map>
#include <string>
#include "sprite.h"
#include <vector>
#include "globals.h"

class AnimatedSprite : public Sprite
{
public:
	AnimatedSprite();
	AnimatedSprite(Graphics &graphics, const std::string &filepath, int sourceX, int sourceY, int width, int height, int positionX, int positionY, int timeToUpdate);
	~AnimatedSprite();
	void playAnimation(std::string animation, bool once = false);

	void update(int elapsedTime);
	void draw(Graphics &graphics, int x, int y);

protected:
	int _timeToUpdate;
	bool _currentAnimationOnce;
	std::string _currentAnimation;

	void addAnimation(int frames, int x, int y, std::string name, int width, int height, Vector2 offset);

	void resetAnimations();

	void stopAnimation();
	void setVisible(bool isVisible);
	//pure virtual
	virtual void animationDone(std::string currentAnimation) = 0;
	virtual void setupAnimations() =0 ;

private:
	std::map<std::string, std::vector<SDL_Rect>> _animations;
	std::map<std::string, Vector2> _offsets;

	unsigned int _frameIndex;
	int _timeElapsed;
	bool _visible;



};
#endif // !ANIMATED_SPRITE_H
