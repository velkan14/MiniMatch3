#include "Menu.h"
#include "Game.h"

Menu::Menu(std::string text) : Screen() {
	text_to_write = text;
}

Menu::~Menu() {
	TTF_CloseFont(font);
}

void Menu::init()
{
	text = new Texture();
	font = TTF_OpenFont("assets/EFRogue.ttf", 56);
	if (font == NULL)
	{
		std::cout << "Failed to load font! Error: " << TTF_GetError() << std::endl;
	}
	for (int i = 0; i < TOTAL; i++) {
		text->load_from_text(font, text_to_write.c_str(), text_color);
	}
}

bool Menu::input(SDL_Event* e) {
    if (e->type == SDL_MOUSEBUTTONDOWN) {
		touch_me = true;
        return true;
    }
    else if (e->type == SDL_MOUSEBUTTONUP) {
        if (touch_me) is_completed = true;
        touch_me = false;
    }
    return false;
}

void Menu::process(float delta_time)
{
}

void Menu::render()
{
	SDL_SetRenderDrawColor(Game::renderer, 0x00, 0x00, 0x00, 255);
	SDL_RenderFillRect(Game::renderer, &fillRect);
	text->render((SCREEN_WIDTH - text->get_width())/ 2 , (SCREEN_HEIGHT - text->get_height()) / 2);
}
