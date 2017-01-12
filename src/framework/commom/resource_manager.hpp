#ifndef _RESOURCE_MANAGER_HPP_
#define _RESOURCE_MANAGER_HPP_

#include <string>
#include <fstream>

#include <graphics/shader.hpp>

class ResourceManager{
public:
	static std::string getImage(const std::string& image) { return std::string("resourcers/images/") + image; }
	static std::string getFont(const std::string& font) { return std::string("resourcers/fonts/") + font; }
	static std::string getSound(const std::string& sound) { return std::string("resourcers/sounds/") + sound; }
	static std::string getShader(const std::string& shader) { return std::string("resources/shaders/") + shader; }

	static ShaderPtr loadShader(const std::string& shader, ShaderType type) {
		ShaderPtr shaderptr(new Shader());

		shaderptr->load(getShader(shader), type);
		return shaderptr;
	}
};

#endif