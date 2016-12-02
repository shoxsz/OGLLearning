#ifndef _TEXTURE_MANAGER_HPP_
#define _TEXTURE_MANAGER_HPP_

#include <unordered_map>
#include <string>

#include "texture.hpp"

class TextureManager{
private:
    static TextureManager* texManager;
public:

    static TextureManager* get(){
        if(texManager == nullptr)
            texManager = new TextureManager();
        return texManager;
    }

    //add the texture, if a texture with the given name already exists it will be replaced
    void add(const std::string& name, Texture2DPtr texture);
    //load the texture: add it to the managed textures and return it
    Texture2DPtr load(const std::string& texture, bool mipmaps = true);
    Texture2DPtr get(const std::string& texture, bool mipmaps = true);
    bool remove(const std::string& texture);

private:
    std::unordered_map<std::string, Texture2DPtr> textures;
};

#endif