#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>

class Texture
{
public:

    Texture();
    virtual ~Texture();

    bool load_from_file(std::string path);
    bool load_from_text(TTF_Font* font, std::string textureText, SDL_Color textColor);
    void free();
    void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Rect* rect = NULL, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

    int get_width();
    int get_height();

private:
    SDL_Texture* texture;

    int width;
    int height;
};
