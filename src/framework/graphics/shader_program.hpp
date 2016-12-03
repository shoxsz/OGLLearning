#ifndef _SHADER_PROGRAM_HPP_
#define _SHADER_PROGRAM_HPP_

#include "definitions.hpp"
#include "shader.hpp"
#include "utils/matrix.hpp"

#include <vector>

struct AttributeSpec {
	std::string name;
	unsigned int local;

	AttributeSpec():local(0){}
	AttributeSpec(const std::string& name, unsigned int local) :name(name), local(local){}
};

class ShaderProgram{
public:
    //copy is not allowed
    ShaderProgram(const ShaderProgram& program) = delete;
    ShaderProgram& operator=(const ShaderProgram& program) = delete;

	ShaderProgram():linked(false), program(0){}
    ~ShaderProgram(){dispose();}

    void dispose();

	//pre link configuration

    void setVertexShader(ShaderPtr vertexShader){
        this->vertexShader = vertexShader;
    }

    void setFragmentShader(ShaderPtr fragmentShader){
        this->fragmentShader = fragmentShader;
    }

	void link(const std::initializer_list<AttributeSpec>& attributes = {});
    void bind();

	unsigned int getUniformLocation(const std::string& name) { return glGetUniformLocation(program, name.c_str()); }

	void loadValue(int uniform, float value) { glUniform1f(uniform, value); }
	void loadVector(int uniform, std::array<float, 2>& vec) { glUniform2fv(uniform, 2, vec.data()); }
	void loadVector(int uniform, std::array<float, 3>& vec) { glUniform3fv(uniform, 3, vec.data()); }
	void loadVector(int uniform, std::array<float, 4>& vec) { glUniform4fv(uniform, 4, vec.data()); }
	void loadMatrix(int uniform, Matrix<float, 2, 2>& mat, bool transpose = false) { glUniformMatrix2fv(uniform, 1, transpose, mat.get()); }
	void loadMatrix(int uniform, Matrix<float, 3, 3>& mat, bool transpose = false) { glUniformMatrix3fv(uniform, 1, transpose, mat.get()); }
	void loadMatrix(int uniform, Matrix<float, 4, 4>& mat, bool transpose = false) { glUniformMatrix4fv(uniform, 1, transpose, mat.get()); }

	void loadValue(int uniform, int value) { glUniform1i(uniform, value); }
	void loadVector(int uniform, std::array<int, 2>& vec) { glUniform2iv(uniform, 2, vec.data()); }
	void loadVector(int uniform, std::array<int, 3>& vec) { glUniform3iv(uniform, 3, vec.data()); }
	void loadVector(int uniform, std::array<int, 4>& vec) { glUniform4iv(uniform, 4, vec.data()); }


    bool isLinked()const{
        return linked;
    }
private:
    void checkProgramError();

    bool linked;
    unsigned int program;

	ShaderPtr vertexShader;
	ShaderPtr fragmentShader;
};

#endif