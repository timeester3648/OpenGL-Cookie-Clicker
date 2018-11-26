#pragma once

#include "../../text/Font.h"
#include "../../shaders/TextShader.h"

#include <string>
#include <glm\glm.hpp>

typedef glm::vec2 Vec2;
typedef glm::vec4 Vec4;

class Label;

class TextRenderer {

	public:

		enum class Alignment {

			Left,
			Center,
			Right

		};

	public:

		TextShader& shader;
		std::vector<Label*> labels;

	public:

		TextRenderer(TextShader& shader);

	private:

		void pre_render(std::string text, Vec2 position, const Font* font, Vec4 color, Alignment alignment, float max_width);

	public:

		void addLabel(Label* label);
		void drawString(std::string text, Vec2 position, const Font* font, Vec4 color, Alignment alignment = Alignment::Left, float max_width = -1.0f);
		void render();
		void render(Label* label);

};