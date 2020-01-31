#pragma once
#include "Texture.h"
#include "vec.h"
#include "Constants.h"

class Board;

class Gem
{
public:
    Gem(Board * b);
    virtual ~Gem() {}
    virtual bool input(SDL_Event* e);
    virtual void process(float delta_time);
    virtual void render();

    void set_texture(Texture* tex);
    void set_position(float x, float y);
    void set_position(vec2 position);
    void set_target(float x, float y);
    void set_target(vec2 target);
    void set_type(gem_type type);
    gem_type get_type() const;
    bool is_neighbor(Gem* g);
    bool is_dragging() const;
    void set_swapping();
    void destroy();

    bool is_moving = false;
    bool is_placing = true;
    bool animating = false;
    int i = 0, j = 0;
    vec2 pos;
    int match = 0;
    bool selected = false;
protected:

private:
    float const margin_swap = 20.0;

    Board* board;

    vec2 target_pos;
    float time_to_target = 0.0;

    //Mouse variables
    bool dragging = false;
    bool touch_me = false;
    vec2 drag_offset;
    vec2 mouse_initial_position;
    vec2 mouse_current_position;

    bool is_swapping = false;
    float angle;
    gem_type type = EMPTY;
    float speed = 500.0;
    int animating_counter = 0;
    Texture* texture = NULL;

};