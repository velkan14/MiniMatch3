// MiniMatch3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <SDL.h>
#include "src/Game.h"

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;
const int FPS = 60;

Game* game = NULL;

int main(int argc, char* args[])
{
    game = new Game();

    if (!game->init(SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT))
    {
        std::cout << "Error initializing Engine" << std::endl;
    }
    else
    {
        while (game->running())
        {
            game->input();
            game->process();
            game->render();
        }
        game->clean();
    }

    return 0;
}
