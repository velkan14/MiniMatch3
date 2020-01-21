#pragma once
#include "Texture.h"
#include "vec.h"

class Gem
{
public:
    Gem();
    virtual ~Gem() {}
    virtual bool input(SDL_Event* e);
    virtual void process();
    virtual void render(SDL_Renderer* gRenderer);
    void setTexture(Texture* tex);
    void setPosition(float x, float y);
    bool is_moving = false;
    bool is_placing = true;
    bool is_neighbor(Gem* g);
    int type = 0;
    int i, j;
    vec2 pos;
    int match = 0;
protected:

private:
    float speed = 2.0;
    vec2 target_pos;
    Texture* texture;

};