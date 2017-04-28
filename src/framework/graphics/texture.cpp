#include "texture.hpp"

Texture2D::Texture2D(const Size& size, PixelFormat format) {
	updatePixels(nullptr, size, format);
}

Texture2D::~Texture2D() {
	dispose();
}

void Texture2D::dispose() {
	if (created) {
		glDeleteTextures(1, &id);
		created = false;
	}
}

void Texture2D::bind() {
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, id);
}

void Texture2D::setWrapping(Wrapping wrap) {
	this->wrap = wrap;
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);
}

void Texture2D::setFiltering(Filtering minFilter, Filtering magFilter) {
	this->minFilter = minFilter;
	this->magFilter = magFilter;

	if (hasMipmap) {
		minFilter = (minFilter == Nearest ? NearestMipmap : LinearMipmap);
		magFilter = (magFilter == Nearest ? NearestMipmap : LinearMipmap);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
	}
	else {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
	}
}


void Texture2D::updatePixels(void* pixels, const Size& size, PixelFormat format, unsigned int mipmapLevel) {
	if (!created) {
		glGenTextures(1, &id);
		created = true;
	}

	bind();
	glTexImage2D(GL_TEXTURE_2D, mipmapLevel, format, size.width, size.height, 0, format, GL_UNSIGNED_BYTE, pixels);
	this->size = size;

	if (mipmapLevel > 0)
		hasMipmap = true;
}

void Texture2D::updatePixelsCompressed(void* pixels, const Size& dimensions, unsigned int size, CompressedFormat comp_format, unsigned int mipmapLevel) {
	if (!created) {
		glGenTextures(1, &id);
		created = true;
	}

	bind();
	glCompressedTexImage2D(GL_TEXTURE_2D, mipmapLevel, comp_format, dimensions.width, dimensions.height, 0, size, pixels);
	this->size = dimensions;

	if (mipmapLevel > 0)
		hasMipmap = true;
}

void Texture2D::buildMipmaps(unsigned int min, unsigned int max) {
	mipmapsRange(min, max);
	hasMipmap = true;

	//update filtering to mipmap filters
	setFiltering(minFilter, magFilter);

	glGenerateMipmap(GL_TEXTURE_2D);
}


void Texture2D::mipmapsRange(unsigned int min, unsigned int max) {
	bind();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, min);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, max);
}