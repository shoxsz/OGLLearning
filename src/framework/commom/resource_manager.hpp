#ifndef _RESOURCE_MANAGER_HPP_
#define _RESOURCE_MANAGER_HPP_

#include <string>
#include <fstream>

#include <sdl\sdl_app.hpp>
#include <graphics\shader.hpp>

class ResourceManager{
public:
	static std::string getImage(const std::string& image) { return SDLApplication::getInstance()->getAppDir() + std::string("resources\\images\\") + image; }
	static std::string getFont(const std::string& font) { return SDLApplication::getInstance()->getAppDir() + std::string("resources\\fonts\\") + font; }
	static std::string getSound(const std::string& sound) { return SDLApplication::getInstance()->getAppDir() + std::string("resources\\sounds\\") + sound; }
	static std::string getShader(const std::string& shader) { return SDLApplication::getInstance()->getAppDir() + std::string("resources\\shaders\\") + shader; }

	static ShaderPtr loadShader(const std::string& shader, ShaderType shadertType) {
		ShaderPtr shaderptr(new Shader());
		shaderptr->load(getShader(shader), shadertType);
		return shaderptr;
	}
};

#endif