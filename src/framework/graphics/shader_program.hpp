#ifndef _SHADER_PROGRAM_HPP_
#define _SHADER_PROGRAM_HPP_

#include "shader.hpp"

class ShaderProgram{
public:

    //copy is not allowed
    ShaderProgram(const ShaderProgram& program) = delete;
    ShaderProgram& operator=(const ShaderProgram& program) = delete;
    ~ShaderProgram(){dispose();}

    void dispose();

    void setVertexShader(ShaderPtr vertexShader){
        this->vertexShader = vertexShader;
    }

    void setFragmentShader(ShaderPtr fragmentShader){
        this->fragmentShader = fragmentShader;
    }

    void link();
    void bind();

    bool isLinked()const{
        return linked;
    }

protected:
    virtual void preLink(){}
private:
    void checkProgramError();

    bool linked;
    unsigned int program;

    ShaderPtr vertexShader;
    ShaderPtr fragmentShader;
};

#endif