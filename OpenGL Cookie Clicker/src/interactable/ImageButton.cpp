#include "../../header/interactable/ImageButton.h"
#include "../../header/util/MathHelper.h"
#include "../../header/display/DisplayManager.h"

ImageButton::ImageButton(Vec2 position, Vec2 scale, TexturedModel* textured_model) : Button(position, scale), textured_model(textured_model) {

}

Vec2 ImageButton::getTextureOffset() const {

	int x = int(this->offset.x);
	int y = int(this->offset.y);
	int rows = textured_model->getTexture().getNumberOfRows();
	int cols = textured_model->getTexture().getNumberOfColumns();

	float spriteWidth = 1.0f / cols;
	float spriteHeight = 1.0f / rows;

	return { spriteWidth * x, spriteHeight * y };

}