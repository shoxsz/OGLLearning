#include "graphics/shader.hpp"

#include "utils/pointer_allocator.hpp"

void Shader::dispose(){
    if(loaded){
        if(attached)
            detach();
		glDeleteShader();
        loaded = false;
        compiled = false;
    }
}

void Shader::load(const std::string& file){
    std::ifstream source(file);
    load(source);
}

void Shader::load(std::ifstream& source){
    char* line;
    char vertexType[1025];
    std::vector<char*, pointer_allocator<char*>> file_lines;

    if(!source.is_open())
        throw std::runtime_error("Failed to load shader!");

    //the first line must identify the shader type
    source.getline(vertexType, 1024);
    if(!strcmp(vertexType, "vertex")){
        type = VertexShader;
    }else if(!strcmp(vertexType, "fragment")){
        type = FragmentShader;
    }else{
        throw std::runtime_error("Shader type not specified!");
    }

    while(!source.eof()){
        line = new line[1025];
        source.getline(line, 1024);

        if(source.fail())
            throw std::runtime_error("Failed to read shader source!");

        file_lines.push_back(line);
    }

     shader = glCreateShader(type);
     glShaderSource(shader, fileLine.data(), nullptr);
     checkErrors();
     loaded = true;
}

void Shader::compile(){
    if(loaded){
        glCompileShader(shader);
        checkErrors();
        compiled = true;
    }
}

void Shader::attachToProgram(unsigned int program){
    if(compiled){
        glAttachShader​(program​, shader​);
        checkProgramError(program);
        attached = true;
        this->program = program;
    }
}

void Shader::detach(){
    if(attached){
        glDetachShader​(program​, shader​);
        program = 0;
        attached = false;
    }
}

void Shader::checkErrors(GLenum param){
    int status;
    glGetShaderiv(shader, param, &status);

    if(status == GL_FALSE){
        unsigned int log_size;
        std::vector<char> log;

        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_size);
        log.resize(log_size);

        glGetShaderInfoLog(shader, log_size, nullptr, log.data());
        log[log_size] = '\0';

        throw std::runtime_error(log.data());
    }
}