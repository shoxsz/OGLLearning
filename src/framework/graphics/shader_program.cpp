#include "shader_program.hpp"

#include <vector>

void ShaderProgram::dispose(){
    if(linked){
        glDeleteProgram(program);
        linked = false;
    }
}

void ShaderProgram::link(){
    if(!vertexShader || !fragmentShader)
        return;

    if(linked)
        dispose();

    program = glCreateProgram();

    vertexShader->attachToProgram(program);
    fragmentShader->attachToProgram(program);

    preLink();

    glLinkProgram(program);
    checkProgramError();
    linked = true;

    vertexShader->detach();
    fragmentShader->detach();
}

void ShaderProgram::bind(){
    if(linked){
        glUseProgram(program);
    }
}

void ShaderProgram::checkProgramError(){
    int status = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &status);

    if(status == GL_FALSE){
        int log_size;
        std::vector<char> log;

        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_size);
        log.resize(log_size);

        glGetProgramInfoLog(program, log_size, nullptr, log.data());
        log[log_size] = '\0';

        throw std::runtime_error(log.data());
    }
}