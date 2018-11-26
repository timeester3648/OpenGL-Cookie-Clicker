#include "../../header/objects/StaticImage.h"
#include "../../header/handler/ModelHandler.h"

StaticImage::StaticImage(Vec2 position, Vec2 scale, TexturedModel* textured_model, float rotation, Vec2 offset) : position(position), scale(scale), textured_model(textured_model), rotation(rotation), offset(offset) {

}

Vec2 StaticImage::getTextureOffset() const {

	int x = int(this->offset.x);
	int y = int(this->offset.y);
	int rows = textured_model->getTexture().getNumberOfRows();
	int cols = textured_model->getTexture().getNumberOfColumns();

	float spriteWidth = 1.0f / cols;
	float spriteHeight = 1.0f / rows;

	return { spriteWidth * x, spriteHeight * y };

}