#pragma once
#pragma once
#include <SDL.h>

class Screen
{
public:
    Screen() {}
    virtual ~Screen() {}
    virtual void init() {}
    virtual bool input(SDL_Event* e) { return false; }
    virtual void process(float delta_time) {}
    virtual void render(){}
    bool completed() {
        return is_completed;
    }

protected:
    bool is_completed = false;

private:
};

