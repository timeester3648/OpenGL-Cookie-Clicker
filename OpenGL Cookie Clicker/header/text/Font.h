#pragma once

#include <glm\glm.hpp>
#include <EOUL\File.hpp>
#include <string>
#include <freetype-gl/texture-atlas.h>
#include <freetype-gl/texture-font.h>
#include <freetype-gl/vertex-buffer.h>
#include <freetype-gl/mat4.h>

typedef glm::vec2 Vec2;

using namespace EOUL::IO;

class Font {

	public:

		ftgl::texture_atlas_t* atlas = nullptr;
		ftgl::texture_font_t* font = nullptr;
		ftgl::vertex_buffer_t* buffer = nullptr;
		ftgl::mat4 mvp;
		File file;
		float size;
		bool preloaded;

	public:

		Font(File file, float size, bool preload = false);
		Font(std::string file, float size, bool preload = false);

		~Font();

	public:

		float getWidth(const std::string& text) const;
		float getHeight(const std::string& text) const;
		Vec2 getSize(const std::string& text) const;

		void setWindowSize(uint64_t width, uint64_t height);

};