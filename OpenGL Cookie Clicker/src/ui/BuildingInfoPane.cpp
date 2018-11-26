#include "../../header/ui/BuildingInfoPane.h"
#include "../../header/handler/ModelHandler.h"
#include "../../header/display/DisplayManager.h"
#include "../../header/game/PlayerData.h"
#include "../../header/util/Formatter.h"
#include "../../header/handler/FontHandler.h"
#include "../../header/util/MathHelper.h"
#include "../../header/shop/ShopPrices.h"
#include "../../header/handler/ShopHandler.h"
#include "../../header/Main.h"

#define EOUL_USE_GLFW_INPUT

#include <EOUL\Maths.h>
#include <EOUL\Utils.h>

using namespace EOUL::Math;
using namespace EOUL::Util;

BuildingInfoPane::BuildingInfoPane(std::string title, std::string description, Vec2 icon_offset, int index) : StaticImage({ (.84 + (.07f - .01875f * .5f) * 2.0f * .75f) - .35f - ((.07f - .01875f * .5f) * 6.0f) - .01875f, 0.0f }, { (.07f - .01875f * .5f) * 6.0f, (.07f - .01875f * .5f) * 2.0f }, ModelHandler::getModelById(13)), index(index) {

	Vec2 icon_scale = { .07f - .01875f * .5f, .07f - .01875f * .5f };

	this->icon = new StaticImage(this->position - (this->scale * Vec2(1.0f, -1.0f)) + (icon_scale * Vec2(1.1f, -1.2f)), icon_scale, ModelHandler::getModelById(7), 0.0f, icon_offset);
	this->title = new Label(title, MathHelper::glfwToTextCoord(this->icon->position + (this->icon->scale * Vec2(1.1f, .35f)), { 1.0f, 1.0f }), FontHandler::getFont("Merriweather-Black", 12.0f));
	this->price = new Label(Formatter::formatCookies(ShopPrices::getPrice(this->index)), MathHelper::glfwToTextCoord(this->icon->position + (this->scale * Vec2(1.75f, 0.2f)), { 1.0f, 1.0f }), FontHandler::getFont("Merriweather-Black", 13.0f), { 0.0f, 1.0f, 0.0f, 1.0f }, TextRenderer::Alignment::Right);
	this->label = new Label("[owned: " + std::to_string(*PlayerData::amounts[this->index]) + "]", MathHelper::glfwToTextCoord(this->icon->position + (this->icon->scale * Vec2(1.1f, -.2f)), { 1.0f, 1.0f }), FontHandler::getFont("Merriweather-Black", 10.0f));
	this->description = new Label(description, MathHelper::glfwToTextCoord(this->icon->position - Vec2(this->icon->scale.x - .03f, .1f), { 1.0f, 1.0f }), FontHandler::getFont("Merriweather-Black", 10.0f), { 1.0f, 1.0f, 1.0f, 1.0f }, TextRenderer::Alignment::Left, 250.0f);
	this->money_icon = new StaticImage((MathHelper::textToGLFWCoord(this->price->position - Vec2(this->price->font->getWidth(Formatter::formatCookies(ShopPrices::getPrice(this->index, 1), 3)) * .55f, 0.0f)) - Vec2(-.01f, 1.5f * .0175f)), Vec2(.0175f, .0175f), ModelHandler::getModelById(8));

	this->borders.push_back(new StaticImage(this->position - (this->scale * Vec2(1.0f, 0.0f)), { .01375f, this->scale.y }, ModelHandler::getModelById(14)));
	this->borders.push_back(new StaticImage(this->position - (this->scale * Vec2(-1.0f, 0.0f)), { .01375f, this->scale.y }, ModelHandler::getModelById(14)));
	this->borders.push_back(new StaticImage(this->position - (this->scale * Vec2(0.0f, 1.0f)), { .01375f, this->scale.x * 1.04f }, ModelHandler::getModelById(9), 90.0f));
	this->borders.push_back(new StaticImage(this->position - (this->scale * Vec2(0.0f, -1.0f)), { .01375f, this->scale.x * 1.04f }, ModelHandler::getModelById(9), 90.0f));

}

BuildingInfoPane::~BuildingInfoPane() {

	this->make_invisible();

	for (auto& panel : this->borders) {

		delete panel;

	}

	this->borders.clear();
	this->borders.shrink_to_fit();

	delete this->icon;
	delete this->money_icon;
	delete this->title;
	delete this->description;
	delete this->price;
	delete this->label;

}

void BuildingInfoPane::setPos(Vec2 position) {

	size_t amount = 1;

	if (isKeyDown(DisplayManager::window, GLFW_KEY_LEFT_CONTROL)) {

		amount = 10;

	} else if (isKeyDown(DisplayManager::window, GLFW_KEY_LEFT_SHIFT)) {

		amount = 100;

	}

	Vec2 old_pos = this->position;
	Vec2 diff = position - this->position;

	this->position += diff;
	this->icon->position += diff;
	this->money_icon->position += diff;

	this->title->position = MathHelper::glfwToTextCoord(this->icon->position + (this->icon->scale * Vec2(1.1f, .35f)), { 1.0f, 1.0f });
	this->price->position = MathHelper::glfwToTextCoord(this->icon->position + (this->scale * Vec2(1.75f, 0.2f)), { 1.0f, 1.0f });
	this->label->position = MathHelper::glfwToTextCoord(this->icon->position + (this->icon->scale * Vec2(1.1f, -.2f)), { 1.0f, 1.0f });
	this->description->position = MathHelper::glfwToTextCoord(this->icon->position - Vec2(this->icon->scale.x - .03f, .1f), { 1.0f, 1.0f });
	this->money_icon->position.x = ((MathHelper::textToGLFWCoord(this->price->position - Vec2(this->price->font->getWidth(Formatter::formatCookies(ShopPrices::getPrice(this->index, amount), 3)), 0.0f)) - Vec2(-.04f, 1.5f * .0175f))).x;

	for (auto& panel : this->borders) {

		panel->position += diff;

	}

}

void BuildingInfoPane::update() {

	size_t amount = 1;

	if (isKeyDown(DisplayManager::window, GLFW_KEY_LEFT_CONTROL)) {

		amount = 10;

	} else if (isKeyDown(DisplayManager::window, GLFW_KEY_LEFT_SHIFT)) {

		amount = 100;

	}

	this->label->text = "[owned: " + std::to_string(*PlayerData::amounts[this->index]) + "]";

	if (PlayerData::cookies >= ShopPrices::getPrice(this->index, amount)) {

		this->price->color = { .4f, 1.0f, .4f, 1.0f };

	} else {

		this->price->color = { 1.0f, .4f, .4f, 1.0f };

	}

}

void BuildingInfoPane::make_visible() {

	if (!this->visible && !ShopHandler::locked[this->index]) {

		this->visible = true;

		auto& arr = renderer->info_pane_renderer.building_info_panes;

		for (auto& pane : arr) {

			if (pane == this) {

				return;

			}

		}

		renderer->info_pane_renderer.addBuildingInfoPane(this);

	}

}

void BuildingInfoPane::make_invisible() {

	if (this->visible) {

		this->visible = false;

		auto& arr = renderer->info_pane_renderer.building_info_panes;

		size_t i = 0;
		for (auto& pane : arr) {

			if (this == pane) {

				arr.erase(arr.begin() + i);

				return;

			}

			i++;

		}

	}

}