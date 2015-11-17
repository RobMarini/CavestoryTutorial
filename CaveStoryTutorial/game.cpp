#include "SDL.h"
#include "game.h"
#include "graphics.h"
#include "input.h"
#include <algorithm>

namespace{
	const int FRAMES_PER_SECOND = 50;
	const int MS_PER_SECOND = 1000;
	const int MAX_SKIPPED_FRAMES = 5;
	const int MAX_FRAME_TIME = MAX_SKIPPED_FRAMES * MS_PER_SECOND / FRAMES_PER_SECOND; 
}
Game::Game(){
	SDL_Init(SDL_INIT_EVERYTHING);
	this->gameLoop();
}
Game::~Game(){

}

void Game::gameLoop(){
	//do a whole frame
	Graphics graphics;
	Input input;
	SDL_Event event;
	_player = Player(graphics, 100, 100);
	_level = Level("map1", Vector2(100, 100), graphics);
	int LAST_UPDATE_TIME = SDL_GetTicks(); //start our timer
	while (true){
		input.beginNewFrame();
		while (SDL_PollEvent(&event)){
			if (event.type == SDL_QUIT){
				return;
			}
			switch (event.type){
			case SDL_KEYDOWN:
				if (event.key.repeat == 0){
					input.keyDownEvent(event);
				}
				break;
			case SDL_KEYUP:
				input.keyUpEvent(event);
				break;
			default:
				break;
			}
			if (input.wasKeyPressed(SDL_SCANCODE_ESCAPE)){
				return;
			}
			else if (input.isKeyHeld(SDL_SCANCODE_LEFT)){
				_player.moveLeft();
			}
			else if (input.isKeyHeld(SDL_SCANCODE_RIGHT)){
				_player.moveRight();
			}
			if (!input.isKeyHeld(SDL_SCANCODE_LEFT) && !input.isKeyHeld(SDL_SCANCODE_RIGHT)){
				_player.stopMoving();
			}
			//Timing for each frame (for physics)
			const int CURRENT_TIME_MS = SDL_GetTicks();
			int ELAPSED_TIME_MS = CURRENT_TIME_MS - LAST_UPDATE_TIME;
			this->update(std::min(ELAPSED_TIME_MS, MAX_FRAME_TIME));
			LAST_UPDATE_TIME = CURRENT_TIME_MS;

			draw(graphics);
		}
	}
}
void Game::draw(Graphics &graphics){
	graphics.clear();
	//LEVEL BEFORE PLAYER
	_level.draw(graphics);
	_player.draw(graphics);
	graphics.flip();
	
}

void Game::update(int elapsedTime){
	_level.update(elapsedTime);
	_player.update(elapsedTime);
}