#include "../../../header/display/render/InfoPaneRenderer.h"
#include "../../../header/util/MathHelper.h"
#include "../../../header/display/DisplayManager.h"

#include <EOUL\Maths.h>

using namespace EOUL::Math;

InfoPaneRenderer::InfoPaneRenderer(StaticShader& shader) : shader(shader) {

}

void InfoPaneRenderer::render() {

	this->shader.start();

	for (auto& pane : this->upgrade_info_panes) {

		this->prepareTexturedModel(pane->textured_model);
		this->prepareInstance(pane);

		glDrawElements(GL_TRIANGLES, pane->textured_model->getRawModel().getVertexCount(), GL_UNSIGNED_INT, 0);

		this->unbindTexturedModel();
		this->prepareTexturedModel(pane->icon->textured_model);
		this->prepareInstance(pane->icon);

		glDrawElements(GL_TRIANGLES, pane->icon->textured_model->getRawModel().getVertexCount(), GL_UNSIGNED_INT, 0);

		this->unbindTexturedModel();
		this->prepareTexturedModel(pane->money_icon->textured_model);
		this->prepareInstance(pane->money_icon);

		glDrawElements(GL_TRIANGLES, pane->money_icon->textured_model->getRawModel().getVertexCount(), GL_UNSIGNED_INT, 0);

		this->unbindTexturedModel();
		this->prepareTexturedModel(pane->borders[0]->textured_model);

		for (size_t i = 0; i < pane->borders.size(); i++) {

			this->prepareInstance(pane->borders[i]);

			glDrawElements(GL_TRIANGLES, pane->money_icon->textured_model->getRawModel().getVertexCount(), GL_UNSIGNED_INT, 0);

		}

		this->unbindTexturedModel();

	}

	for (auto& pane : this->building_info_panes) {

		this->prepareTexturedModel(pane->textured_model);
		this->prepareInstance(pane);

		glDrawElements(GL_TRIANGLES, pane->textured_model->getRawModel().getVertexCount(), GL_UNSIGNED_INT, 0);

		this->unbindTexturedModel();
		this->prepareTexturedModel(pane->icon->textured_model);
		this->prepareInstance(pane->icon);

		glDrawElements(GL_TRIANGLES, pane->icon->textured_model->getRawModel().getVertexCount(), GL_UNSIGNED_INT, 0);

		this->unbindTexturedModel();
		this->prepareTexturedModel(pane->money_icon->textured_model);
		this->prepareInstance(pane->money_icon);

		glDrawElements(GL_TRIANGLES, pane->money_icon->textured_model->getRawModel().getVertexCount(), GL_UNSIGNED_INT, 0);

		this->unbindTexturedModel();
		this->prepareTexturedModel(pane->borders[0]->textured_model);

		for (size_t i = 0; i < pane->borders.size(); i++) {

			this->prepareInstance(pane->borders[i]);

			glDrawElements(GL_TRIANGLES, pane->money_icon->textured_model->getRawModel().getVertexCount(), GL_UNSIGNED_INT, 0);

		}

		this->unbindTexturedModel();

	}

	this->shader.stop();

}

void InfoPaneRenderer::prepareInstance(const StaticImage* image) {

	glm::mat4 mat = MathHelper::createTransformationMatrix({ image->position.x, image->position.y }, image->rotation, { image->scale.x, image->scale.y });

	this->shader.loadOffset(image->getTextureOffset());
	this->shader.loadTransformationMatrix(mat);
	this->shader.loadMixColor(image->doMixColor, image->mixColor, image->mixIntensity);
	this->shader.loadIconLocked(image->blacked_out);

}

void InfoPaneRenderer::prepareTexturedModel(const TexturedModel* model) {

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

void InfoPaneRenderer::unbindTexturedModel() {

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glBindVertexArray(0);

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);

}

void InfoPaneRenderer::addUpgradeInfoPane(UpgradeInfoPane* info_pane) {

	this->upgrade_info_panes.push_back(info_pane);

}

void InfoPaneRenderer::addBuildingInfoPane(BuildingInfoPane* info_pane) {

	this->building_info_panes.push_back(info_pane);

}