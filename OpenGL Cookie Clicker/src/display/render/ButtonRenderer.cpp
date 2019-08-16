#include "../../../header/display/render/ButtonRenderer.h"
#include "../../../header/display/DisplayManager.h"
#include "../../../header/handler/ModelHandler.h"
#include "../../../header/util/MathHelper.h"
#include "../../../header/handler/InteractableHandler.h"
#include "../../../header/shop/ShopTile.h"

#include <EOUL\Maths.hpp>

using namespace EOUL::Math;

ButtonRenderer::ButtonRenderer(StaticShader& shader) : shader(shader) {

}

void ButtonRenderer::render() {

	this->shader.start();

	for (auto& it : this->buttons) {

		this->prepareTexturedModel(it.first);

		for (auto& button : it.second) {

			this->prepareInstance(button);

			glDrawElements(GL_TRIANGLES, button->textured_model->getRawModel().getVertexCount(), GL_UNSIGNED_INT, 0);

		}

		this->unbindTexturedModel();

	}

	this->shader.stop();

}

void ButtonRenderer::prepareInstance(const ImageButton* button) {

	glm::mat4 mat = MathHelper::createTransformationMatrix(button->position, 0, { button->scale.x, button->scale.y });

	this->shader.loadOffset(button->getTextureOffset());
	this->shader.loadTransformationMatrix(mat);
	this->shader.loadMixColor(button->doMixColor, button->mixColor, button->mixIntensity);
	this->shader.loadIconLocked(false);

}

void ButtonRenderer::prepareTexturedModel(const TexturedModel* model) {

	RawModel& rawModel = model->getRawModel();
	ModelTexture& texture = model->getTexture();

	glBindVertexArray(rawModel.getVaoID());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glActiveTexture(GL_TEXTURE0);

	this->shader.loadNumberOfRows(texture.getNumberOfRows());
	this->shader.loadNumberOfColumns(texture.getNumberOfColumns());

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); 

	glBindTexture(GL_TEXTURE_2D, texture.getID());

}

void ButtonRenderer::unbindTexturedModel() {

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glBindVertexArray(0);

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);

}

void ButtonRenderer::addImageButton(ImageButton* button) {

	this->buttons.insert(std::map<TexturedModel*, std::vector<ImageButton*>>::value_type(button->textured_model, std::vector<ImageButton*>()));
	this->buttons[button->textured_model].push_back(button);

	bool contains = false;
	for (auto& interactable : InteractableHandler::interactables) {

		if (dynamic_cast<ImageButton*>(interactable) == button) {

			contains = true;

		}

	}

	if (!contains) {

		InteractableHandler::interactables.push_back(button);

	}

}