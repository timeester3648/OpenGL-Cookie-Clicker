#pragma once

#include "TextureLoader.h"

#include <GL\glew.h>

class Texture {

	friend class TextureLoader;

	public:

		unsigned char* img;
		int width, height;
		GLuint textureID;

	private:

		Texture() = delete;
		Texture(const Texture& copy) = delete;
		Texture(const char* path, bool repeat = false, bool font = false);
		Texture(unsigned char* pixels, int width, int height, bool repeat = false);

	public:

		GLuint getTextureID() const;

		void updatePixels(unsigned char* pixels);

};