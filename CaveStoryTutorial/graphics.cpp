/*
*Graphics!
*/
#include "graphics.h"
#include "SDL.h"
#include "SDL_image.h"
#include "globals.h"

Graphics::Graphics()
{
	//create window
	SDL_CreateWindowAndRenderer(globals::SCREEN_WIDTH, globals::SCREEN_HEIGHT, 0, &_window, &_renderer);
	SDL_SetWindowTitle(_window, "Cavestory");
}

Graphics::~Graphics()
{
	//destroy window
	SDL_DestroyWindow(_window);
}

SDL_Surface* Graphics::loadImage(const std::string &filepath){
	if (_spriteSheets.count(filepath) == 0){
		_spriteSheets[filepath] = IMG_Load(filepath.c_str()); //if it fails, it returns NULL
	}
	return this->_spriteSheets[filepath];
}

void Graphics::blitSurface(SDL_Texture* texture, SDL_Rect* sourceRectangle, SDL_Rect* destinationRectangle){
	SDL_RenderCopy(_renderer, texture, sourceRectangle, destinationRectangle);
}

void Graphics::flip(){
	SDL_RenderPresent(_renderer);
}

void Graphics::clear(){
	SDL_RenderClear(_renderer);
}

SDL_Renderer* Graphics::getRenderer() const{ return _renderer; }