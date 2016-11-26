#include "shader.hpp"

#include "utils/pointer_allocator.hpp"

#include <fstream>
#include <algorithm>

class shader_allocator

void Shader::load(const std::string& file){
    std::ifstream source(file);
    std::vector<char*, pointer_allocator<char*, true>> file_lines;

    if(!source.is_open())
        throw std::runtime_error("Failed to load shader!");

    source.getline(line, 1024);
    if(!strcmp(line, "vertex")){
        type = VertexShader;
    }else if(!strcmp(line, "fragment")){
        type = FragmentShader;
    }else{
        throw std::runtime_error("Shader type not specified!");
    }

    while(!source.eof()){
        source.getline(line, 1024);
        file_lines.push_back(std::string(line, strlen(line)));
    }

     shader = glCreateShader(type);
     glShaderSource(shader, fileLine.data(), nullptr);
}

void Shader::compile(){

}

void Shader::checkErrors(){

}