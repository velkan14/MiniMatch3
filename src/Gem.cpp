#include "Gem.h"
#include <iostream>
#include <cmath>
#include "Board.h"

Gem::Gem(Board* b)
{
    board = b;
    angle = 0.0;
}

bool Gem::input(SDL_Event* e) {
    if (touch_me && e->type == SDL_MOUSEMOTION) {
        int x, y;
        SDL_GetMouseState(&x, &y);
        mouse_current_position = vec2(float(x), float(y));
        drag_offset = mouse_current_position - mouse_initial_position;
        dragging = true;
        return true;
    }
    else if (e->type == SDL_MOUSEBUTTONDOWN) {
            int x, y;
            SDL_GetMouseState(&x, &y);
            if (pos.x < x && x < pos.x + 75 && pos.y < y && y < pos.y + 75.0) {
                touch_me = true;
                mouse_initial_position = vec2(float(x), float(y));
                return true;
            }
    }
    else if (e->type == SDL_MOUSEBUTTONUP) {
        if (is_dragging()) set_target(vec2(margin_x + i * 70.0, margin_y + j * 70.0));
        if (touch_me) board->select_gem(this);
        touch_me = false;
        dragging = false;
    }
    return false;
}

void Gem::process(float delta_time) {
    float vstep = 0.8f * delta_time;
    if (is_swapping) vstep = 3.0 * delta_time;
    time_to_target = time_to_target + 1.0f * vstep;
    if (time_to_target > 1.0f) {
        time_to_target = 1.0f;
    }
    if (time_to_target > 0.7f) {
        is_placing = false;
        is_swapping = false;
    }
    pos = lerp(pos, target_pos, time_to_target);
    if (is_dragging()) {
        pos = pos + drag_offset;
    }
    if (is_dragging()) {
        if (pos.x > margin_x + (i + 1) * 70 - margin_swap) {
            board->swap_gem(this, i + 1, j);
            touch_me = false;
            dragging = false;
        }
        else if (pos.x < margin_x + (i - 1) * 70 + margin_swap) {
            board->swap_gem(this, i - 1, j);
            touch_me = false;
            dragging = false;
        }
        else if (pos.y > margin_y + (j + 1) * 70 - margin_swap) {
            board->swap_gem(this, i , j + 1);
            touch_me = false;
            dragging = false;
        }
        else if (pos.y < margin_y + (j - 1) * 70 + margin_swap) {
            board->swap_gem(this, i , j - 1);
            touch_me = false;
            dragging = false;
        }
    }
    if (animating && animating_counter > 70) {
        animating = false;
    }
    else {
        animating_counter = animating_counter + 5;
    }
}

void Gem::render() {
    SDL_Point p = { 35 , 35 };
    SDL_Rect rec = { pos.x, pos.y, 70, 70 };
    if (selected || is_dragging()) {
        rec.x = rec.x + 5;
        rec.y = rec.y + 5;
        rec.w = rec.w - 10;
        rec.h = rec.h - 10;
    }
    if (animating) {
        rec.x = rec.x + animating_counter / 2.0f;;
        rec.y = rec.y + animating_counter / 2.0f;
        rec.w = rec.w - animating_counter;
        rec.h = rec.h - animating_counter;
    }
    texture->render(pos.x, pos.y, NULL, 0.0, &rec, &p);
}

void Gem::set_texture(Texture* tex) {
    texture = tex;
}

void Gem::set_position(float x, float y) {
    set_position(vec2(x, y));
}

void Gem::set_position(vec2 p) {
    pos = p;
}

void Gem::set_target(float x, float y) {
    set_target(vec2(x, y));
}

void Gem::set_target(vec2  target) {
    target_pos = target;
    time_to_target = 0.0;
    is_placing = true;
}

bool Gem::is_neighbor(Gem* g)
{
    if (i == g->i) {
        if (j + 1 == g->j) return true;
        if (j - 1 == g->j) return true;
    }
    else if (j == g->j) {
        if (i + 1 == g->i) return true;
        if (i - 1 == g->i) return true;
    }
    return false;
}

bool Gem::is_dragging() const
{
    return dragging;
}

void Gem::set_swapping()
{
    is_swapping = true;
}

void Gem::destroy()
{
    animating = true;
    animating_counter = 0;
}

void Gem::set_type(int t) {
    type = t;
}

int Gem::get_type() const {
    return type;
}