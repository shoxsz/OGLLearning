#include "shader_program.hpp"
#include "shader.hpp"

#include <vector>

void ShaderProgram::dispose(){
    if(linked){
        glDeleteProgram(program);
        linked = false;
    }
}

void ShaderProgram::link(const std::initializer_list<AttributeSpec>& attributes){
    if(!vertexShader || !fragmentShader)
        return;

    if(linked)
        dispose();

    program = glCreateProgram();

    vertexShader->attachToProgram(program);
    fragmentShader->attachToProgram(program);

	for (const AttributeSpec& attr : attributes) {
		glBindAttribLocation(program, attr.local, attr.name.c_str());
	}

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
        GLsizei max_size;
        std::vector<char> log;

        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &max_size);
        log.resize(max_size+1);

        glGetProgramInfoLog(program, max_size, nullptr, log.data());
        log[max_size] = '\0';

        throw std::runtime_error(log.data());
    }
}