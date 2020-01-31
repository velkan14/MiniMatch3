#pragma once
#include <SDL.h>
#include "Constants.h"

class Transition
{
public:
    const int SPEED = 10;
    Transition();
    ~Transition();
    void init();
    bool input(SDL_Event* e);
    void process(float delta_time);
    void render();

    void in();
    void out();
    bool completed();

private:
    SDL_Rect fillRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
    int alpha = 255;
    bool transitioning = false;
    int value = SPEED;
};