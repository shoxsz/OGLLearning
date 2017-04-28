#include "texture_manager.hpp"

#include <SDL_image.h>

#include "dds_loader.hpp"

void TextureManager::add(const std::string& name, Texture2DPtr texture) {
	textures[name] = texture;
}

Texture2DPtr TextureManager::load(const std::string& texture, bool mipmaps) {
	auto tex = textures.find(texture);

	if (tex == textures.end()) {

		std::string ext = texture.substr(texture.size() - 3, 3);

		if (ext == "dds") {
			return loadDDS(texture);
		}
		else {
			return loadBMP(texture);
		}
	}
	else {
		return tex->second;
	}
}

bool TextureManager::remove(const std::string& texture) {
	return (textures.erase(texture) > 0);
}

Texture2DPtr TextureManager::loadDDS(const std::string& file) {
	DDSLoader loader;
	return loader.load(file);
}

Texture2DPtr TextureManager::loadBMP(const std::string& file) {
	Texture2DPtr tex2D;
	SDL_Surface* image;
	PixelFormat format;

	image = IMG_Load(file.c_str());

	if (image == nullptr)
		throw std::runtime_error(SDL_GetError());

	switch (image->format->BytesPerPixel) {
	case 4:
		format = RGBA;
		break;
	case 3:
		format = RGB;
		break;
	}

	tex2D.reset(new Texture2D());
	tex2D->updatePixels(image->pixels, Size(image->w, image->h), format);

	textures[file] = tex2D;

	return tex2D;
}