#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Board.h"
#include "Texture.h".

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
    SDL_Event* event;

    Texture* text;
    Board* board;
    bool isRunning = false;
    int tick = 0;

};

