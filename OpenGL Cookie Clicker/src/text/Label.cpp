#include "../../header/text/Label.h"
#include "../../header/display/render/TextRenderer.h"
#include "../../header/Main.h"

Label::Label(std::string text, Vec2 position, const Font* font, Vec4 color, TextRenderer::Alignment alignment, float max_width) : text(std::move(text)), position(position), font(font), color(color), alignment(alignment), max_width(max_width) {

}

void Label::remove() {

	size_t i = 0;
	for (auto& label : renderer->text_renderer.labels) {

		if (this == label) {

			renderer->text_renderer.labels.erase(renderer->text_renderer.labels.begin() + i);

			break;

		}

		i++;

	}

}