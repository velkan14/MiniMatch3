#pragma once
#include <string>
#include ""
class TextureLoader
{
public:
    TextureLoader();
    virtual ~TextureLoader();
    void init();

    Texture* load_texture(std::string name);
private:

}
