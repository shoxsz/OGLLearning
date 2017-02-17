#ifndef _RESOURCE_MANAGER_HPP_
#define _RESOURCE_MANAGER_HPP_

#include <string>
#include <fstream>

#include <graphics/shader.hpp>
#include <graphics/texture_manager.hpp>

class ResourceManager{
public:
	static std::string getImage(const std::string& image) { return std::string("resources/images/") + image; }
	static std::string getFont(const std::string& font) { return std::string("resources/fonts/") + font; }
	static std::string getSound(const std::string& sound) { return std::string("resources/sounds/") + sound; }
	static std::string getShader(const std::string& shader) { return std::string("resources/shaders/") + shader; }

	static ShaderPtr loadShader(const std::string& shader, ShaderType type) {
		ShaderPtr shaderptr(new Shader());

		shaderptr->load(getShader(shader), type);
		return shaderptr;
	}

	static Texture2DPtr loadTexture(const std::string& texture, bool useMipmaps = true){
		return TextureManager::instance()->load(getImage(texture), useMipmaps);
	}
};

#endif