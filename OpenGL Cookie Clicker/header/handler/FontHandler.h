#pragma once

#include "../text/Font.h"

#include <vector>

class FontHandler {

	friend class DisplayManager;
	
	private:

		struct FontData {

			std::string name;
			float size;
			Font* font;

		};

	private:

		static std::vector<FontData> fonts;

	public:

		static void addFont(std::string filename, float size, bool preload = true);
		static void cleanUp();

		static const Font* getFont(std::string name, float size, bool preload = true);

};