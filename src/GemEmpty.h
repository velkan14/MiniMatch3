#pragma once
#include "Gem.h"

class GemEmpty : public Gem
{
public:
    GemEmpty(): Gem(){}
    virtual ~GemEmpty() {}
    virtual bool input(SDL_Event* e) override { return false; }
    virtual void process() override {}
    virtual void render(SDL_Renderer* gRenderer) override {}
protected:

private:

};