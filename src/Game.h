#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Board.h"

class Game
{
public:
    Game();
    virtual ~Game();

    bool init(int pos_x, int pos_y, int screen_width, int screen_height);
    void input();
    void process();
    void render();
    bool running() const;
    void clean();

    static SDL_Renderer* renderer;
protected:

private:
    SDL_Window* window;
    SDL_Surface* surface;

    Board* board;
    bool isRunning = false;
    int tick = 0;
    float delta_time = 0.0;
    unsigned int last_frame_ticks = 0;

};

