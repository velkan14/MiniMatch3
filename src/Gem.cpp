#include "Gem.h"
#include <iostream>
#include <cmath>

Gem::Gem()
{
}

bool Gem::input(SDL_Event* e) {
    if (is_moving && e->type == SDL_MOUSEMOTION) {
        int x, y;
        SDL_GetMouseState(&x, &y);
        if (pos.x - 70 < x && x < pos.x + 70 * 2 && pos.y - 70 < y && y < pos.y + 70 * 2) {
            target_pos = vec2(x - 35.0, y - 35.0);
        }
        else {
            is_moving = false;
        }
        if (pos.x < x && x < pos.x + 70 && pos.y < y && y < pos.y + 70) return true;
    }
    else
        if (e->type == SDL_MOUSEBUTTONDOWN) {
            int x, y;
            SDL_GetMouseState(&x, &y);
            if (pos.x < x && x < pos.x + 70 && pos.y < y && y < pos.y + 70) {
                target_pos = vec2(x - 35.0, y - 35.0);
                is_moving = true;
                return true;
            }
        }
        else if (e->type == SDL_MOUSEBUTTONUP) {
            is_moving = false;
        }
    return false;
}

void Gem::process(float delta_time) {
    float const margin_x = 232.0;
    float const margin_y = 104.0;
    if(!is_moving) target_pos = vec2(margin_x + i * 70.0, margin_y + j * 70);
    vec2 direction = target_pos - pos;
    if ( direction.norm() < 4.0) {
        //std::cout << direction.norm() << std::endl;
        pos = vec2(margin_x + i * 70.0, margin_y + j * 70);
        is_placing = false;
    }
    else {
        is_placing = true;
        vec2 normalized = direction.normalize();
        pos = pos + (normalized * speed * delta_time);
    }
}

void Gem::render() {
    texture->render(pos.x, pos.y);
}

void Gem::set_texture(Texture* tex) {
    texture = tex;
}

void Gem::set_position(float x, float y) {
    target_pos = vec2(x, y);
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

void Gem::set_type(int t) {
    type = t;
}

int Gem::get_type() const {
    return type;
}