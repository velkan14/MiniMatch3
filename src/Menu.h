#pragma once
#include <SDL_ttf.h>
#include "Screen.h"
#include "Texture.h"
#include "Constants.h"

class Menu : public Screen {
public:
    Menu(std::string text);
    virtual ~Menu() {}
    void init() override;
    bool input(SDL_Event* e) override;
    void process(float delta_time) override;
    void render() override;

private:
    SDL_Rect fillRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
    TTF_Font* font = NULL;
    SDL_Color text_color = { 255, 255, 0 };
    Texture* text = NULL;
    bool touch_me = false;
    std::string text_to_write = "";
};