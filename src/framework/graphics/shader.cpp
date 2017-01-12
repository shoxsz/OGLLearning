#include "graphics/shader.hpp"

#include <vector>
#include <fstream>
#include <cstring>

void Shader::dispose(){
    if(loaded){
        if(attached)
            detach();
		glDeleteShader(shader);
        loaded = false;
        compiled = false;
    }
}

void Shader::load(const std::string& file, ShaderType type){
    std::ifstream source(file);
    
    load(source, type);
}

void Shader::load(std::istream& source, ShaderType type){
    unsigned int line_size;
    char* line;
    char vertexType[1025];
    std::vector<char*> file_lines;

    if(!source.good())
        throw std::runtime_error("bad std::istream passed!");

    while(!source.eof()){
        //no lines should be greater than 1024 bytes
        line = new char[1026];
        source.getline(line, 1024);

        line_size = strlen(line);
        line[line_size] = '\n';
        line[line_size + 1] = '\0';

        if(source.fail())
            throw std::runtime_error("Failed to read shader source!");

        file_lines.push_back(line);
    }

    shader = glCreateShader(type);
	glShaderSource(shader, file_lines.size(), file_lines.data(), nullptr);
    loaded = true;

	for (char* line : file_lines)
	    delete[] line;
    
    this->type = type;
}

void Shader::compile(){
    if(loaded){
        glCompileShader(shader);
		checkErrors(GL_COMPILE_STATUS);
        compiled = true;
    }
}

void Shader::attachToProgram(unsigned int program){
    if(compiled){
		//this can fail if the program is not valid!
		glAttachShader(program, shader);
        attached = true;
        this->program = program;
    }
}

void Shader::detach(){
    if(attached){
		glDetachShader(program, shader);
        program = 0;
        attached = false;
    }
}

void Shader::checkErrors(GLenum param){
    int status;
    glGetShaderiv(shader, param, &status);

    if(status == GL_FALSE){
        int log_size;
        std::vector<char> log;

        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_size);
        log.resize(log_size + 1);

        glGetShaderInfoLog(shader, log_size, nullptr, log.data());
        log[log_size] = '\0';

        throw std::runtime_error(log.data());
    }
}