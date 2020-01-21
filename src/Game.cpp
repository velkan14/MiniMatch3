#include "Game.h"
#include <iostream>

SDL_Renderer* Game::renderer = NULL;

Game::Game()
{
    //ctor
}

Game::~Game()
{
    //dtor
}

bool Game::init(int pos_x, int pos_y, int screen_width, int screen_height)
{
    bool success = false;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Error initializing SDL:" << SDL_GetError() << std::endl;
    }
    else
    {
        window = SDL_CreateWindow("Game", pos_x, pos_y, screen_width, screen_height, SDL_WINDOW_SHOWN);

        if (window == NULL)
        {
            std::cout << "Error creating Window." << SDL_GetError() << std::endl;
        }
        else
        {
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

            if (renderer == NULL)
            {
                std::cout << "Error creating Renderer." << SDL_GetError() << std::endl;
            }
            else
            {
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags))
                {
                    std::cout << "Error initializing IMG." << IMG_GetError() << std::endl;
                }
                else
                {
                    //Initialize renderer color
                    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
                    surface = SDL_GetWindowSurface(window);
                    success = true;
                    isRunning = true;
                }
            }
        }
    }

    /*text = new BTexture();
    if (!text->loadFromFile("assets//gems/Color-1.png")) {
        std::cout << "Failed to load image foo.png" << std::endl;
        success = false;
    }
    */
    board = new Board();
    board->init();

    return success;
}

void Game::input()
{
    SDL_Event e;
    while (SDL_PollEvent(&e) != NULL)
    {
        if (e.type == SDL_QUIT)
        {
            isRunning = false;
        }
        board->input(&e);
    }
}

void Game::process()
{
    tick++;
    board->process();
}

void Game::render()
{
    SDL_RenderClear(renderer);
    board->render(renderer);
    SDL_RenderPresent(renderer);
}

bool Game::running() const
{
    return isRunning;
}

void Game::clean()
{
    //Destroy window
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = NULL;
    renderer = NULL;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}
