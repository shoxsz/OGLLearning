#include "texture_manager.hpp"

#include <SDL_opengl.h>
#include "third/lodepng.hpp"

void TextureManager::load(const std::string& texture){
    unsigned int pos = texture.find_last_of('.');

    if(pos == std::string::npos)
        throw std::runtime_error("image extension not specified!");

    std::string ext = text.substr(pos);

    if(ext == "png"){
        //load png
    }else if(ext == "bmp"){
        //load bmp
    }
}

Texture2DPtr TextureManager::get(const std::string& texture){
    auto& tex = texture.find(texture);

    if(tex == textures.end())
        return Texture2DPtr(nullptr);
    
    return tex->second;
}

bool TextureManager::remove(const std::string& texture){
    return (textures.erase(texture) > 0);
}