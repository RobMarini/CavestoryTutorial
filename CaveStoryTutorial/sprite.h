#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include "SDL.h"

class Graphics; //forward declare

class Sprite
{
public:
	Sprite();
	Sprite(Graphics &graphics, const std::string &filepath, int sourceX, int sourceY, int width, int height, int positionX, int positionY);
	virtual ~Sprite();
	virtual void update();
	void draw(Graphics &graphics, int x, int y);

protected:
	SDL_Rect _sourceRect;
	SDL_Texture* _spriteSheet;
	int _x, _y;

private:

};

#endif