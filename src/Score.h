#pragma once
#include "Constants.h"
#include "Texture.h"
#include <SDL.h>
#include <SDL_ttf.h>

class Score
{
public:
    Score(int black_n, int white_n, int pink_n, int blue_n, int orange_n);
    virtual ~Score() {}
    void init();
    bool input(SDL_Event* e);
    void process(float delta_time);
    void render();

    void miss_swap();
    void add_gem_destroyed(gem_type type, int number);
    int get_missed_swapes();
    int get_gem_destroyed(gem_type type);
    int get_destroyed();
    bool passed();

protected:

private:
    TTF_Font* font = NULL;
    SDL_Color text_color = { 0, 0, 0 };
    Texture* gems[TOTAL] = { NULL, NULL, NULL, NULL, NULL, NULL };
    Texture* texts[TOTAL] = { NULL, NULL, NULL, NULL, NULL, NULL };
    int gems_destroyed[TOTAL] = { 0, 5, 5, 5, 5, 5 };
    int missed_swapes = 0;
    int total_destroyed = 0;
};