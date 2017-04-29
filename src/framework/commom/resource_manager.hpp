#ifndef _RESOURCE_MANAGER_HPP_
#define _RESOURCE_MANAGER_HPP_

#include <string>
#include <fstream>

#include <sdl\sdl_app.hpp>
#include <graphics\shader.hpp>
#include <graphics\texture_manager.hpp>
#include <graphics\obj_loader.hpp>
#include <graphics\skn_loader.hpp>

class ResourceManager{
public:
	static std::string getModel(const std::string& model) { return SDLApplication::getInstance()->getAppDir() + std::string("resources\\models\\") + model; }
	static std::string getImage(const std::string& image) { return SDLApplication::getInstance()->getAppDir() + std::string("resources\\images\\") + image; }
	static std::string getFont(const std::string& font) { return SDLApplication::getInstance()->getAppDir() + std::string("resources\\fonts\\") + font; }
	static std::string getSound(const std::string& sound) { return SDLApplication::getInstance()->getAppDir() + std::string("resources\\sounds\\") + sound; }
	static std::string getShader(const std::string& shader) { return SDLApplication::getInstance()->getAppDir() + std::string("resources\\shaders\\") + shader; }

	static ShaderPtr loadShader(const std::string& shader, ShaderType shadertType) {
		ShaderPtr shaderptr(new Shader());
		shaderptr->load(getShader(shader), shadertType);
		return shaderptr;
	}

	static Texture2DPtr loadTexture(const std::string& texture, bool useMipmaps = true) {
		return TextureManager::instance()->load(getImage(texture), useMipmaps);
	}

	static void loadOBJ(const std::string& model, ModelPtr& M) {
		OBJLoader loader;
		loader.load(getModel(model), M);
	}

	static void loadSKN(const std::string& model, std::vector<ModelPtr>& M) {
		SKNLoader loader;
		loader.load(getModel(model), M);
	}
};

#endif