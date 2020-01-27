#include "Texture.h"
#include "Game.h"
#include <iostream>

Texture::Texture()
{

}

Texture::~Texture()
{

}

//Loads image at specified path
bool Texture::loadFromFile(std::string path)
{
    bool success = true;
    SDL_Surface* sur = IMG_Load(path.c_str());

    if (sur == NULL)
    {
        std::cout << "Error loading png: " << IMG_GetError() << std::endl;
        success = false;
    }
    else {
        tTexture = SDL_CreateTextureFromSurface(Game::renderer, sur);
        if (tTexture == NULL) {
            std::cout << "Error creating texture." << SDL_GetError() << std::endl;
            success = false;
        }
        tWidth = sur->w;
        tHeight = sur->h;
        SDL_FreeSurface(sur);
    }
    return success;
}

//Deallocates texture
void Texture::free()
{

}

//Renders texture at given point
void Texture::render(int x, int y, SDL_Rect* clip, double angle, SDL_Rect* dest_rect, SDL_Point* center, SDL_RendererFlip flip)
{
    if (dest_rect == NULL) {
        SDL_Rect rect = { x, y, tWidth, tHeight };
        if (clip != NULL)
        {
            rect.w = clip->w;
            rect.h = clip->h;
        }
        SDL_RenderCopyEx(Game::renderer, tTexture, clip, &rect, angle, center, flip);
    }
    else {
        SDL_RenderCopyEx(Game::renderer, tTexture, clip, dest_rect, angle, center, flip);
    }
    
    //SDL_RenderCopy(Game::renderer, tTexture, NULL, &dest_rect);
}


//Gets image dimensions
int Texture::getWidth()
{
    return tWidth;
}
int Texture::getHeight()
{
    return tHeight;
}

void Texture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{

}

//Set blending
void Texture::setBlendMode(SDL_BlendMode blending)
{

}

//Set alpha modulation
void Texture::setAlpha(Uint8 alpha)
{

}
