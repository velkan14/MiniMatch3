#include "Score.h"

#include <iostream>

#include "Game.h"

Score::Score(int black_n, int white_n, int pink_n, int blue_n, int orange_n)
{
	gems_destroyed[BLACK] = black_n;
	gems_destroyed[WHITE] = white_n;
	gems_destroyed[PINK] = pink_n;
	gems_destroyed[BLUE] = blue_n;
	gems_destroyed[ORANGE] = orange_n;

	for (int i = 0; i < TOTAL; i++) {
		texts[i] = new Texture();
	}
}

void Score::init()
{
	gems[BLACK] = Game::texture_loader->load_texture("assets/Color-1.png");
	gems[WHITE] = Game::texture_loader->load_texture("assets/Color-2.png");
	gems[PINK] = Game::texture_loader->load_texture("assets/Color-3.png");
	gems[BLUE] = Game::texture_loader->load_texture("assets/Color-4.png");
	gems[ORANGE] = Game::texture_loader->load_texture("assets/Color-5.png");

	font = TTF_OpenFont("assets/EFRogue.ttf", 28);
	if (font == NULL)
	{
		std::cout << "Failed to load font! Error: " << TTF_GetError() << std::endl;
	}
	for (int i = 0; i < TOTAL; i++) {
		texts[i]->load_from_text(font, "x 0", text_color);
	}

}

bool Score::input(SDL_Event* e)
{
	return false;
}

void Score::process(float delta_time)
{
}

void Score::render()
{
	gems[BLACK]->render(15, MARGIN_Y );
	texts[BLACK]->render(90, MARGIN_Y + 30);

	gems[WHITE]->render(15, MARGIN_Y + 10 + 70);
	texts[WHITE]->render(90, MARGIN_Y + 30 + 70);

	gems[PINK]->render(15, MARGIN_Y + 10 + 70 * 2);
	texts[PINK]->render(90, MARGIN_Y + 30 + 70 * 2);

	gems[BLUE]->render(15, MARGIN_Y + 10 + 70 * 3);
	texts[BLUE]->render(90, MARGIN_Y + 30 + 70 * 3);

	gems[ORANGE]->render(15, MARGIN_Y + 10 + 70 * 4);
	texts[ORANGE]->render(90, MARGIN_Y + 30 + 70 * 4);
}

void Score::miss_swap()
{
	missed_swapes++;
}

void Score::add_gem_destroyed(gem_type type, int number)
{
	gems_destroyed[type] -= number;
	if (gems_destroyed[type] < 0) gems_destroyed[type] = 0;
	texts[type]->load_from_text(font, "x " + std::to_string(gems_destroyed[type]), text_color);
	total_destroyed += number;

}

int Score::get_missed_swapes()
{
	return missed_swapes;
}

int Score::get_gem_destroyed(gem_type type)
{
	return gems_destroyed[type];
}

int Score::get_destroyed()
{
	return total_destroyed;
}

bool Score::passed()
{
	for (int i = 0; i < TOTAL; i++) {
		if (gems_destroyed[i] != 0) {
			return false;
		}
	}
	return true;
}

