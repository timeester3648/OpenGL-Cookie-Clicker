#pragma once

#include "Font.h"
#include "../display/render/TextRenderer.h"

#include <glm\glm.hpp>
#include <string>

typedef glm::vec2 Vec2;
typedef glm::vec4 Vec4;

class TextRenderer;

class Label {

	public:

		std::string text;
		Vec2 position;
		Vec4 color;
		const Font* font;
		TextRenderer::Alignment alignment;
		float max_width;

	public:

		Label(std::string text, Vec2 position, const Font* font, Vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f }, TextRenderer::Alignment alignment = TextRenderer::Alignment::Left, float max_width = -1.0f);

		virtual ~Label() = default;

	public:

		void remove();

};