#include "../../header/text/Font.h"
#include "../../header/loading/texture/TextureLoader.h"
#include "../../header/display/DisplayManager.h"

#include <freetype-gl\freetype-gl.h>

Font::Font(File file, float size, bool preload) : file(std::move(file)), size(size), preloaded(preload) {

	this->atlas = ftgl::texture_atlas_new(512, 512, 1);
	this->font = ftgl::texture_font_new_from_file(this->atlas, this->size, this->file.getAbsolutePath().u8string().c_str());
	this->buffer = ftgl::vertex_buffer_new("vertex:3f,tex_coord:2f,color:4f");

	if (this->font == nullptr) {

		throw std::runtime_error("Could not load font");

	}

	ftgl::mat4_set_identity(&this->mvp);

	if (this->preloaded) {

		for (unsigned char i = 0; i < 255 && i != -1; i++) {

			texture_glyph_t* glyph = texture_font_get_glyph(this->font, (char*) &i);

		}

		glDeleteTextures(1, &this->atlas->id);
		glGenTextures(1, &this->atlas->id);
		glBindTexture(GL_TEXTURE_2D, this->atlas->id);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, (GLsizei) font->atlas->width, (GLsizei) font->atlas->height, 0, GL_RED, GL_UNSIGNED_BYTE, this->atlas->data);

	}

	this->setWindowSize(DisplayManager::width, DisplayManager::height);

}

Font::Font(std::string file, float size, bool preload) : Font(File(file), size, preload) {

}

Font::~Font() {

	if (this->atlas != nullptr) {

		ftgl::texture_atlas_delete(this->atlas);

		this->atlas = nullptr;

	}

	if (this->font != nullptr) {

		ftgl::texture_font_delete(this->font);

		this->font = nullptr;

	}

	if (this->buffer != nullptr) {

		ftgl::vertex_buffer_delete(this->buffer);

		this->buffer = nullptr;

	}

}

void Font::setWindowSize(uint64_t width, uint64_t height) {

	ftgl::mat4_set_orthographic(&this->mvp, 0, float(width), 0, float(height), -1, 1);

}

float Font::getWidth(const std::string& text) const {

	using namespace ftgl;

	float width = 0.0f;

	for (int i = 0; i < text.size(); i++) {

		texture_glyph_t* glyph = texture_font_get_glyph(this->font, &text[i]);

		if (i > 0) {

			float kerning = texture_glyph_get_kerning(glyph, &text[i - 1]);

			width += kerning;

		}

		width += glyph->advance_x;

	}

	return width;
}

float Font::getHeight(const std::string& text) const {

	using namespace ftgl;

	float min = 0.0f;
	float max = 0.0f;

	for (int i = 0; i < text.size(); i++) {

		texture_glyph_t* glyph = texture_font_get_glyph(this->font, &text[i]);
		float height = glyph->height;
		float offset = glyph->offset_y - height;

		if (offset < min) {

			min = offset;

		}

		if (height > max) {

			max = height;

		}

	}

	return abs(min) + abs(max);

}

Vec2 Font::getSize(const std::string& text) const {

	return { this->getWidth(text), this->getHeight(text) };

}