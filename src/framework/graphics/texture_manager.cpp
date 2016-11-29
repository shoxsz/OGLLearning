#include "texture_manager.hpp"

#include <SDL_opengl.h>
#include <SDL_image.h>

Texture2Dptr TextureManager::add(const std::string& name, Texture2DPtr texture){
    textures[name] = texture;
}

void TextureManager::load(const std::string& texture, bool mipmaps){
    Texture2DPtr tex2D;
    SDL_Surface* image;
    PixelFormat format;

    image = IMG_Load(texture.c_str());

    if(image == nullptr)
        throw std::runtime_error(SDL_GetError());

    switch(image->format->BytesPerPixel){
        case 4:
            format = RGBA;
        break;
        case 3:
            format = RGB;
        break;
    }

    tex2D.reset(new Texture2D());
    tex2D->write(image->pixels, Size(image->w, image->h), format);

    textures[texture] = tex2D;

    return tex2D;
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