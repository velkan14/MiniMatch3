#include "Game.h"
#include <iostream>
#include "Menu.h"

SDL_Renderer* Game::renderer = NULL;
TextureLoader* Game::texture_loader = NULL;

Game::Game()
{
    texture_loader = new TextureLoader();
    transition = new Transition();
}

Game::~Game()
{
    delete current_screen;
    delete transition;
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
                    if (TTF_Init() == -1)
                    {
                        std::cout << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << std::endl;
                        success = false;
                    }
                    success = true;
                    is_running = true;
                }
            }
        }
    }

    current_screen = get_screen(screen_index++);
    current_screen->init();
    transition->out();
    state = Game::TRANSITION_OUT;

    return success;
}

void Game::input()
{
    SDL_Event e;
    while (SDL_PollEvent(&e) != NULL)
    {
        if (e.type == SDL_QUIT)
        {
            is_running = false;
        }
        current_screen->input(&e);
    }
}

void Game::process()
{
    tick++;
    
    delta_time =  (SDL_GetTicks() - last_frame_ticks) / 1000.f;

    switch (state)
    {
    case Game::PLAYING:
        current_screen->process(delta_time);
        if (current_screen->completed()) {
            transition->in();
            state = Game::TRANSITION_IN;
        }
        break;
    case Game::TRANSITION_IN:
        transition->process(delta_time);
        if (transition->completed()) {
            Screen* next = get_screen(screen_index++);
            delete current_screen;
            current_screen = next;
            current_screen->init();
            transition->out();
            state = Game::TRANSITION_OUT;
        }
        break;
    case Game::TRANSITION_OUT:
        transition->process(delta_time);
        if (transition->completed()) {
            state = Game::PLAYING;
        }
        break;
    default:
        break;
    }
    last_frame_ticks = SDL_GetTicks();
}

void Game::render()
{
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);
    current_screen->render();
    transition->render();
    SDL_RenderPresent(renderer);
}

bool Game::running() const
{
    return is_running;
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

Screen* Game::get_screen(int number)
{
    switch (number)
    {
    case 0:
        return new Menu("Click to Start!");
    case 1:
        return new Menu("Level 1");
    case 2:
        return new Board(new Score(20, 20, 20, 20, 20));
    case 3:
        return new Menu("Level 2");
    case 4:
        return new Board(new Score(30, 30, 30, 30, 30));
    case 5:
        return new Menu("Level 3");
    case 6:
        return new Board(new Score(40, 40, 40, 40, 40));
    case 7:
        //
        return new Menu("Congratulations!!");
    default:
        break;
    }
    return new Menu("Please, close game!");
}
