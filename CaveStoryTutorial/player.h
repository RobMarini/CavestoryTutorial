#ifndef PLAYER_H
#define PLAYER_H

#include "animatedSprite.h"
#include "globals.h"
class Graphics;


class Player : public AnimatedSprite
{
public:
	Player();
	Player(Graphics &graphics, int x, int y);
	~Player();
	void draw(Graphics &graphics);
	void update(int elapsedTime);
	
	void moveLeft();
	void moveRight();
	void stopMoving();

	//implement pure functions
	virtual void animationDone(std::string currentAnimation);
	virtual void setupAnimations() override;

private:
	double _dx, dy;
	Direction _facing;
};

#endif