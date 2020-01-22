#pragma once
#include "Texture.h"
#include "vec.h"

class Gem
{
public:
    Gem();
    virtual ~Gem() {}
    virtual bool input(SDL_Event* e);
    virtual void process(float delta_time);
    virtual void render();
    void set_texture(Texture* tex);
    void set_position(float x, float y);
    void set_type(int type);
    int get_type() const;
    bool is_neighbor(Gem* g);

    bool is_moving = false;
    bool is_placing = true;
    int i = 0, j = 0;
    vec2 pos;
    int match = 0;
protected:

private:
    int type = 0;
    float speed = 500.0;
    vec2 target_pos;
    Texture* texture = NULL;

};