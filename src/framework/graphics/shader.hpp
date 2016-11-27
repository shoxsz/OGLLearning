#ifndef _SHADER_HPP_
#define _SHADER_HPP_

#include "enums.hpp"

#include <string>
#include <fstream>
#include <memory>

class Shader{
public:
    friend class ShaderProgram;

    //copy is not allowed
    Shader(const Shader& shader) = delete;
    Shader& operator=(const Shader& shader) = delete;

    Shader():loaded(false), compiled(false), attached(false){}
    ~Shader(){dispose();}

    void dispose();

    void load(const std::string& file);
    void load(std::ifstream& source);
    void compile();
    void attachToProgram(unsigned int program);
    void detach();

    bool isLoaded()const{ return loaded; }
    bool isCompiled()const{ return compiled; }
    bool isAttached()const{ return attached; }

private:
    void checkErrors(GLenum param);

    bool loaded;
    bool compiled;
    bool attached;
    unsigned int program;
    unsigned int shader;
    ShaderType type;
};

std::shared_ptr<Shader> ShaderPtr;

#endif