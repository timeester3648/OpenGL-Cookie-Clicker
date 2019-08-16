#include "../../../header/display/render/StaticImageRenderer.h"
#include "../../../header/util/MathHelper.h"
#include "../../../header/display/DisplayManager.h"

#include <EOUL\Maths.hpp>

using namespace EOUL::Math;

StaticImageRenderer::StaticImageRenderer(StaticShader& shader) : shader(shader) {

}

void StaticImageRenderer::render() {

	this->shader.start();

	for (auto& it : this->static_images) {

		this->prepareTexturedModel(it.first);

		for (auto& button : it.second) {

			this->prepareInstance(button);

			glDrawElements(GL_TRIANGLES, button->textured_model->getRawModel().getVertexCount(), GL_UNSIGNED_INT, 0);

		}

		this->unbindTexturedModel();

	}

	this->shader.stop();

}

void StaticImageRenderer::render_overlays() {

	this->shader.start();

	for (auto& it : this->overlays) {

		this->prepareTexturedModel(it.first);

		for (auto& button : it.second) {

			this->prepareInstance(button);

			glDrawElements(GL_TRIANGLES, button->textured_model->getRawModel().getVertexCount(), GL_UNSIGNED_INT, 0);

		}

		this->unbindTexturedModel();

	}

	this->shader.stop();

}

void StaticImageRenderer::prepareInstance(const StaticImage* image) {

	glm::mat4 mat = MathHelper::createTransformationMatrix({ image->position.x, image->position.y }, image->rotation, { image->scale.x, image->scale.y });

	this->shader.loadOffset(image->getTextureOffset());
	this->shader.loadTransformationMatrix(mat);
	this->shader.loadMixColor(image->doMixColor, image->mixColor, image->mixIntensity);
	this->shader.loadIconLocked(image->blacked_out);

}

void StaticImageRenderer::prepareTexturedModel(const TexturedModel* model) {

	RawModel& rawModel = model->getRawModel();
	ModelTexture& texture = model->getTexture();

	glBindVertexArray(rawModel.getVaoID());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glActiveTexture(GL_TEXTURE0);

	this->shader.loadNumberOfRows(texture.getNumberOfRows());
	this->shader.loadNumberOfColumns(texture.getNumberOfColumns());

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); 

	glBindTexture(GL_TEXTURE_2D, model->getTexture().getID());

}

void StaticImageRenderer::unbindTexturedModel() {

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glBindVertexArray(0);

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);

}

void StaticImageRenderer::addStaticImage(StaticImage* image) {

	this->static_images.insert(std::map<TexturedModel*, std::vector<StaticImage*>>::value_type(image->textured_model, std::vector<StaticImage*>()));
	this->static_images[image->textured_model].push_back(image);

}

void StaticImageRenderer::addOverlay(StaticImage* image) {

	this->overlays.insert(std::map<TexturedModel*, std::vector<StaticImage*>>::value_type(image->textured_model, std::vector<StaticImage*>()));
	this->overlays[image->textured_model].push_back(image);

}