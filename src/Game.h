#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Board.h"
#include "TextureLoader.h"
#include "Transition.h"

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
    static TextureLoader* texture_loader;
protected:

private:
    enum {
        PLAYING,
        TRANSITION_IN,
        TRANSITION_OUT
    } state;

    SDL_Window* window = NULL;
    SDL_Surface* surface = NULL;

    Screen* current_screen;
    Transition* transition;
    bool is_running = false;
    int tick = 0;
    float delta_time = 0.0;
    unsigned int last_frame_ticks = 0;

    int screen_index = 0;
    Screen* get_screen(int number);
};

