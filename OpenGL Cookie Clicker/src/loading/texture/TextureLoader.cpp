#include "../../../header/loading/texture/TextureLoader.h"
#include "../../../header/loading/texture/Texture.h"

Texture* TextureLoader::getTexture(const char* path, bool font) {

	return new Texture(path, false, font);

}

Texture* TextureLoader::getFontTexture(unsigned char* pixels, int width, int height) {

	return new Texture(pixels, width, height, false);

}
