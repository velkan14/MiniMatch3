#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>

//Texture wrapper class
class Texture
{
public:
    //Initializes variables
    Texture();

    //Deallocates memory
    virtual ~Texture();

    //Loads image at specified path
    bool loadFromFile(std::string path);

    //Deallocates texture
    void free();

    //Renders texture at given point
    void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Rect* rect = NULL, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

    //Gets image dimensions
    int getWidth();
    int getHeight();

    void setColor(Uint8 red, Uint8 green, Uint8 blue);

    //Set blending
    void setBlendMode(SDL_BlendMode blending);

    //Set alpha modulation
    void setAlpha(Uint8 alpha);


private:
    //The actual hardware texture
    SDL_Texture* tTexture;

    //Image dimensions
    int tWidth;
    int tHeight;
};
