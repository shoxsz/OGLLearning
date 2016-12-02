#ifndef _RESOURCE_MANAGER_HPP_
#define _RESOURCE_MANAGER_HPP_

#include <string>

class ResourceManager{
public:
    static std::string getImage(const std::string& image){
        return std::string("../../resourcers/images") + image;
    }

    static std::string getFont(const std::string& font){
        return std::string("../../resourcers/fonts") + font;
    }

    static std::string getSound(const std::string& sound){
        return std::string("../../resourcers/sound") + sound;
    }
    
    static std::string getShader(const std::string& shader){
        return std::string("../../resourcers/shader") + shader;
    }
};

#endif