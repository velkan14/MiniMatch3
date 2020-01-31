#include "TextureLoader.h"
#include <iterator> 
#include <iostream>

TextureLoader::TextureLoader()
{
}

TextureLoader::~TextureLoader() {
    for (MapType::iterator it = textures_map.begin(); it != textures_map.end(); ++it)
    {
        delete it->second;
        textures_map.erase(it);
    }
}

void TextureLoader::init()
{
}

Texture* TextureLoader::load_texture(std::string name)
{
    MapType::iterator lb = textures_map.lower_bound(name);

    if (lb != textures_map.end() && !(textures_map.key_comp()(name, lb->first)))
    {
        return lb->second;
    }
    else
    {
        Texture* temp = new Texture();
        temp->load_from_file(name);
        if (!temp->load_from_file(name)) {
            std::cout << "Failed to load image " << name << std::endl;
        }
        textures_map.insert(lb, MapType::value_type(name, temp));
        return temp;
    }
}
