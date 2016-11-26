#ifndef _TEXTURE_MANAGER_HPP_
#define _TEXTURE_MANAGER_HPP_

#include <unordered_map>
#include <string>

#include "texture.hpp"

class TextureManager{
private:
    TextureManager* texManager;
public:

    static TextureManager* get(){
        if(texManager == nullptr)
            texManager = new TextureManager();
        return texManager;
    }

    void load(const std::string& texture);
    Texture2DPtr get(const std::string& texture);
    bool remove(const std::string& texture);

private:
    std::unordered_map<std::string, Texture2DPtr> textures;
};

#endif