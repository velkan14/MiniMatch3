#include "Gem.h"
#include <iostream>
#include <cmath>

Gem::Gem()
{
    //ctor
}

bool Gem::input(SDL_Event* e) {
    if (is_moving && e->type == SDL_MOUSEMOTION) {
        int x, y;
        SDL_GetMouseState(&x, &y);
        if (true) {
            target_pos = vec2(x - 35, y - 35);
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

void Gem::process() {
    float const margin_x = 232.0;
    float const margin_y = 104.0;
    if(!is_moving) target_pos = vec2(float(margin_x + i * 70.0), float(margin_y + j * 70));
    vec2 direction = target_pos - pos;
    vec2 normalized = direction.normalize();
    //std::cout << direction.norm() << std::endl;
    pos = pos + normalized * speed;

    if ( direction.norm() < 11.0) {
        is_placing = false;
    }
    else {
        is_placing = true;
    }
}

void Gem::render(SDL_Renderer* gRenderer) {
    texture->render(pos.x, pos.y);
}

void Gem::setTexture(Texture* tex) {
    texture = tex;
}

void Gem::setPosition(float x, float y) {
    //pos = vec2(x, y);
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
