#pragma once
#include "Gem.h"

class GemEmpty : public Gem
{
public:
    GemEmpty(Board * b): Gem(b){}
    virtual ~GemEmpty() {}
    virtual bool input(SDL_Event* e) override { return false; }
    virtual void process(float delta_time) override {}
    virtual void render() override {}
protected:

private:

};