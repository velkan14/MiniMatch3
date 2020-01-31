#include "Texture.h"
#include "Game.h"
#include <iostream>

Texture::Texture()
{
    height = 0;
    width = 0;
}

Texture::~Texture()
{
    free();
}

bool Texture::load_from_file(std::string path)
{
    bool success = true;
    SDL_Surface* sur = IMG_Load(path.c_str());

    if (sur == NULL)
    {
        std::cout << "Error loading png: " << IMG_GetError() << std::endl;
        success = false;
    }
    else {
        texture = SDL_CreateTextureFromSurface(Game::renderer, sur);
        if (texture == NULL) {
            std::cout << "Error creating texture." << SDL_GetError() << std::endl;
            success = false;
        }
        width = sur->w;
        height = sur->h;
        SDL_FreeSurface(sur);
    }
    return success;
}

bool Texture::load_from_text(TTF_Font* font, std::string textureText, SDL_Color textColor)
{
    free();

    SDL_Surface* textSurface = TTF_RenderText_Solid(font, textureText.c_str(), textColor);
    if (textSurface == NULL)
    {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
    }
    else
    {
        texture = SDL_CreateTextureFromSurface(Game::renderer, textSurface);
        if (texture == NULL)
        {
            printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
        }
        else
        {
            width = textSurface->w;
            height = textSurface->h;
        }

        SDL_FreeSurface(textSurface);
    }

    return texture != NULL;
}

void Texture::free()
{
    if (texture != NULL)
    {
        SDL_DestroyTexture(texture);
        texture = NULL;
        width = 0;
        height = 0;
    }
}
void Texture::render(int x, int y, SDL_Rect* clip, double angle, SDL_Rect* dest_rect, SDL_Point* center, SDL_RendererFlip flip)
{
    if (dest_rect == NULL) {
        SDL_Rect rect = { x, y, width, height };
        if (clip != NULL)
        {
            rect.w = clip->w;
            rect.h = clip->h;
        }
        SDL_RenderCopyEx(Game::renderer, texture, clip, &rect, angle, center, flip);
    }
    else {
        SDL_RenderCopyEx(Game::renderer, texture, clip, dest_rect, angle, center, flip);
    }
}

int Texture::get_width()
{
    return width;
}
int Texture::get_height()
{
    return height;
}