#pragma once
#include <string>
#include "Texture.h"
#include <map> 
#include <memory>

class TextureLoader
{
public:
    typedef std::map<std::string, Texture*> MapType;

    TextureLoader();
    virtual ~TextureLoader() {}
    void init();

    Texture* load_texture(std::string name);
private:
    MapType textures_map;

};
