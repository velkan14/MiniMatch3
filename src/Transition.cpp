#include "Transition.h"
#include "Game.h"

Transition::Transition()
{
}

void Transition::init()
{
}

bool Transition::input(SDL_Event* e)
{
	return false;
}

void Transition::process(float delta_time)
{
	if (transitioning) {
		alpha += value;
		if (alpha >= 255) {
			transitioning = false;
			alpha = 255;
		}
		else if (alpha <= 0) {
			alpha = 0;
			transitioning = false;
		}
	}
}

void Transition::render()
{
	SDL_SetRenderDrawBlendMode(Game::renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(Game::renderer, 0x00, 0x00, 0x00, alpha);
	SDL_RenderFillRect(Game::renderer, &fillRect);
}

void Transition::in() {
	value = SPEED;
	transitioning = true;
}

void Transition::out() {
	value = -SPEED;
	transitioning = true;
}

bool Transition::completed()
{
	return !transitioning;
}
