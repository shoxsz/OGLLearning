#ifndef _SHADER_HPP_
#define _SHADER_HPP_

#include "enums.hpp"

#include <string>

class Shader{
public:
    enum {max_shader_bytes = 1048576;/*2^20*/}

    Shader():loaded(false), compiled(false){}

    void load(const std::string& file);
    void compile();

    bool isLoaded()const{ return loaded; }
    bool isCompiled()const{ return compiled; }

private:
    void checkErrors();

    bool loaded;
    bool compiled;
    unsigned int shader;
    ShaderType type;
};

#endif