#include "level.h"
#include "graphics.h"
#include "SDL.h"
#include "SDL_image.h"

Level::Level(){}

Level::Level(std::string mapName, Vector2 spawnPoint, Graphics &graphics):
_mapName(mapName),
_spawnPoint(spawnPoint),
_size(Vector2(0,0))
{
	loadMap(_mapName, graphics);
}

Level::~Level(){}

void Level::loadMap(std::string mapName, Graphics &graphics){
	//TEMP
	_backgroundTexture = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage("../Content/BK/bkblue.png"));
	_size = Vector2(1280,960);
}

void Level::update(int elapsedTime){

}

void Level::draw(Graphics &graphics){
	int BG_SIZE = 64;
	SDL_Rect sourceRect = { 0, 0, BG_SIZE, BG_SIZE };
	SDL_Rect destRect = { 0, 0, 0, 0 };
	for (int x = 0; x < _size.x / BG_SIZE; x++){
		for (int y = 0; y < _size.y / BG_SIZE; y++){
			destRect.x = x* BG_SIZE * globals::SPRITE_SCALE;
			destRect.y = y* BG_SIZE * globals::SPRITE_SCALE;
			destRect.w = BG_SIZE * globals::SPRITE_SCALE;
			destRect.h = BG_SIZE * globals::SPRITE_SCALE;
			graphics.blitSurface(_backgroundTexture, &sourceRect, &destRect);
		}
	}
}