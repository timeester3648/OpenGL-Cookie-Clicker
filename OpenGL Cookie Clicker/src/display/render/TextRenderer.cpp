#include "../../../header/display/render/TextRenderer.h"
#include "../../../header/objects/DynamicModel.h"
#include "../../../header/loading/Loader.h"
#include "../../../header/util/MathHelper.h"
#include "../../../header/display/DisplayManager.h"
#include "../../../header/handler/EffectHandler.h"
#include "../../../header/text/Label.h"
#include "../../../header/Main.h"

#include <freetype-gl\freetype-gl.h>
#include <EOUL\Maths.hpp>
#include <vector>
#include <Windows.h>

using namespace EOUL::Math;

namespace {

	typedef struct {

		float x, y, z;
		float s, t;
		float r, g, b, a;

	} vertex_t; 

}

static Mat4 toGLM(ftgl::mat4 mat);

TextRenderer::TextRenderer(TextShader& shader) : shader(shader) {

}

void TextRenderer::render() {

	for (auto& label : this->labels) {

		if (label->text.length() == 0) {

			continue;

		}

		this->drawString(label->text, label->position, label->font, label->color, label->alignment);

	}

	for (auto& info_pane : renderer->info_pane_renderer.upgrade_info_panes) {

		this->render(info_pane->title);
		this->render(info_pane->label);
		this->render(info_pane->price);
		this->render(info_pane->description);

	}

	for (auto& info_pane : renderer->info_pane_renderer.building_info_panes) {

		this->render(info_pane->title);
		this->render(info_pane->label);
		this->render(info_pane->price);
		this->render(info_pane->description);

	}

	for (auto& label : EffectHandler::click_labels) {

		this->render(label);

	}

}

void TextRenderer::addLabel(Label* label) {

	this->labels.push_back(label);

}

void TextRenderer::render(Label* label) {

	if (label != nullptr) {

		this->drawString(label->text, label->position, label->font, label->color, label->alignment, label->max_width);	

	}

}

void TextRenderer::drawString(std::string text, Vec2 position, const Font* font, Vec4 color, Alignment alignment, float max_width) {
	
	this->pre_render(text, position, font, color, alignment, max_width);

	if (!font->preloaded) {

		glDeleteTextures(1, &font->atlas->id);
		glGenTextures(1, &font->atlas->id);
		glBindTexture(GL_TEXTURE_2D, font->atlas->id);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, (GLsizei) font->atlas->width, (GLsizei) font->atlas->height, 0, GL_RED, GL_UNSIGNED_BYTE, font->atlas->data);

	}

	this->shader.start();

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, font->atlas->id);
	
	this->shader.loadMVP(toGLM(font->mvp));

	ftgl::vertex_buffer_render(font->buffer, GL_TRIANGLES);
	ftgl::vertex_buffer_clear(font->buffer);

	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);

	this->shader.stop();

}

void TextRenderer::pre_render(std::string str, Vec2 position, const Font* font, Vec4 color, Alignment alignment, float max_width) {

	float cur_width = 0.0f;
	const char* text = str.c_str();
	ftgl::vec2 pen = { { position.x, position.y } };
	Vec2 real = position;
	size_t i;
	float r = color.r, g = color.g, b = color.b, a = color.a;

	switch (alignment) {

		case Alignment::Center:

			pen.x -= font->getWidth(text) * .5f;

		case Alignment::Left:

			break;

		case Alignment::Right:

			pen.x -= font->getWidth(text);

			break;

		default:

			throw std::runtime_error("Is you DUMB?");

	}

	for (i = 0; i < strlen(text); i++) {

		texture_glyph_t* glyph = texture_font_get_glyph(font->font, text + i);

		if (glyph != NULL) {

			float kerning = 0.0f;

			if (i > 0) {

				kerning = texture_glyph_get_kerning(glyph, text + i - 1);

			}

			if (cur_width > max_width && max_width != -1.0f && str.at(i) == ' ') {

				cur_width = 0.0f;

				pen.x = position.x;
				pen.y -= font->getHeight(str);

			}

			pen.x += kerning;
			cur_width += kerning;

			int x0 = (int) (pen.x + glyph->offset_x);
			int y0 = (int) (pen.y + glyph->offset_y);
			int x1 = (int) (x0 + glyph->width);
			int y1 = (int) (y0 - glyph->height);
			float s0 = glyph->s0;
			float t0 = glyph->t0;
			float s1 = glyph->s1;
			float t1 = glyph->t1;

			GLuint indices[6] = { 0, 1, 2, 0, 2, 3 };

			vertex_t vertices[4] = { 
				
				{ (float) x0, (float) y0, 0, s0, t0, r, g, b, a },
				{ (float) x0, (float) y1, 0, s0, t1, r, g, b, a },
				{ (float) x1, (float) y1, 0, s1, t1, r, g, b, a },
				{ (float) x1, (float) y0, 0, s1, t0, r, g, b, a }

			};

			vertex_buffer_push_back(font->buffer, vertices, 4, indices, 6);

			pen.x += glyph->advance_x;
			cur_width += glyph->advance_x;

		}

	}

}

static Mat4 toGLM(ftgl::mat4 mat) {

	Mat4 tmp = Mat4();

	tmp[0][0] = mat.m00;
	tmp[0][1] = mat.m01;
	tmp[0][2] = mat.m02;
	tmp[0][3] = mat.m03;
	tmp[1][0] = mat.m10;
	tmp[1][1] = mat.m11;
	tmp[1][2] = mat.m12;
	tmp[1][3] = mat.m13;
	tmp[2][0] = mat.m20;
	tmp[2][1] = mat.m21;
	tmp[2][2] = mat.m22;
	tmp[2][3] = mat.m23;
	tmp[3][0] = mat.m30;
	tmp[3][1] = mat.m31;
	tmp[3][2] = mat.m32;
	tmp[3][3] = mat.m33;

	return tmp;

}