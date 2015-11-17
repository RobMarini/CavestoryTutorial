#ifndef  GRAPHICS_H
#define GRAPHICS_H

#include <map>
#include <string>

struct SDL_Window; struct SDL_Renderer; struct SDL_Surface; struct SDL_Texture; struct SDL_Rect; //Forward declare pointers

class Graphics
{
public:
	Graphics();
	~Graphics();

	SDL_Surface* loadImage(const std::string &filePath);
	/*
	draws a texture to a certain part of the screen
	*/
	void blitSurface(SDL_Texture* texture, SDL_Rect* sourceRectangle, SDL_Rect* destinationRectangle);
	/*
	Renders to the screen
	*/
	void flip();

	/*
	clears screen
	*/
	void clear();

	SDL_Renderer* getRenderer() const;

private:
	SDL_Window* _window;
	SDL_Renderer* _renderer;

	std::map<std::string, SDL_Surface*> _spriteSheets; //preload and store images for performance
};


#endif // ! GRAPHICS_H
