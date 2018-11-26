#include "../../header/handler/FontHandler.h"

std::vector<FontHandler::FontData> FontHandler::fonts = std::vector<FontHandler::FontData>();

const Font* FontHandler::getFont(std::string name, float size, bool preload) {

	if (fonts.size() > 0) {

		for (auto& data : fonts) {

			if (data.name == name && data.size == size) {

				return data.font;

			}

		}

	}

	addFont(name, size, preload);

	return getFont(name, size, preload);

}

void FontHandler::addFont(std::string filename, float size, bool preload) {

	fonts.push_back({ filename, size, new Font(std::filesystem::absolute("res/fonts/" + filename + ".ttf").u8string(), size, preload) });

}

void FontHandler::cleanUp() {

	for (auto& data : fonts) {

		delete data.font;

	}

}