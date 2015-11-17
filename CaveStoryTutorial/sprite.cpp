#include "sprite.h"
#include "graphics.h"
#include "iostream"
#include "globals.h"

Sprite::Sprite()
{
}

Sprite::Sprite(Graphics &graphics, const std::string &filepath, int sourceX, int sourceY, int width, int height, int positionX, int positionY) :
_x(positionX),
_y(positionY)
{
	_sourceRect.x = sourceX; _sourceRect.y = sourceY;
	_sourceRect.w = width; _sourceRect.h = height;
	_spriteSheet = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage(filepath));
	if (_spriteSheet == 0){
		std::cout << "Unable to Load Image!";
		std::string s = SDL_GetError();
	}
}

Sprite::~Sprite()
{
}

void Sprite::draw(Graphics &graphics, int x, int y){
	SDL_Rect destinationRectangle = 
	{
		x, y, _sourceRect.w*globals::SPRITE_SCALE, _sourceRect.h*globals::SPRITE_SCALE 
	};
	graphics.blitSurface(_spriteSheet, &_sourceRect, &destinationRectangle);
}

void Sprite::update(){

}