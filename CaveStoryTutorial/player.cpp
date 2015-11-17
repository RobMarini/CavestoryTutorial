#include "player.h"
#include "graphics.h"
#include <math.h>

namespace player_constants{
	const double WALK_SPEED = .2;
}

Player::Player(){}
Player::Player(Graphics &graphics, int x, int y) :
	AnimatedSprite(graphics, "../Content/Sprites/MyChar.png", 0, 0, 16, 16, x, y, 100)
{
	graphics.loadImage("../Content/Sprites/MyChar.png");
	setupAnimations();
	playAnimation("RUNRIGHT");
}
Player::~Player(){}

void Player::setupAnimations(){
	addAnimation(3, 0, 0, "RUNLEFT", 16, 16, Vector2());
	addAnimation(3, 0, 16, "RUNRIGHT", 16, 16, Vector2());
	addAnimation(1, 0, 0, "IDLELEFT", 16, 16, Vector2());
	addAnimation(1, 0, 16, "IDLERIGHT", 16, 16, Vector2());
}

void Player::animationDone(std::string currentAnimation){}

void Player::update(int elapsedTime){
	_x += (int)floor(_dx*elapsedTime);
	AnimatedSprite::update(elapsedTime);
}

void Player::draw(Graphics &graphics){
	AnimatedSprite::draw(graphics, _x, _y);
}

void Player::moveLeft(){
	_facing = LEFT;
	_dx = -player_constants::WALK_SPEED;
	playAnimation("RUNLEFT");
}
void Player::moveRight(){
	_facing = RIGHT;
	_dx = player_constants::WALK_SPEED;
	playAnimation("RUNRIGHT");
}
void Player::stopMoving(){
	_dx = 0;
	switch (_facing){
	case RIGHT:
		playAnimation("IDLERIGHT"); break;
	case LEFT:
		playAnimation("IDLELEFT"); break;
	default: break;
	}
}