#pragma once

class Texture;

class TextureLoader {

	public:

		static Texture* getTexture(const char* path, bool font = false);
		static Texture* getFontTexture(unsigned char* pixels, int width, int height);

};