#include "../../header/ui/UpgradeInfoPane.h"
#include "../../header/handler/ModelHandler.h"
#include "../../header/game/PlayerData.h"
#include "../../header/util/Formatter.h"
#include "../../header/handler/FontHandler.h"
#include "../../header/util/MathHelper.h"
#include "../../header/Main.h"

#include <EOUL\Maths.h>

using namespace EOUL::Math;

UpgradeInfoPane::UpgradeInfoPane(std::string title, std::string description, std::string lore, long double cost, Vec2 icon_offset) : StaticImage({ (.84 + (.07f - .01875f * .5f) * 2.0f * .75f) - .35f - ((.07f - .01875f * .5f) * 6.0f) - .01875f, 0.0f }, { (.07f - .01875f * .5f) * 6.0f, (.07f - .01875f * .5f) * 2.0f }, ModelHandler::getModelById(13)), cost(cost) {

	Vec2 icon_scale = { .07f - .01875f * .5f, .07f - .01875f * .5f };

	this->icon = new StaticImage(this->position - (this->scale * Vec2(1.0f, -1.0f)) + (icon_scale * Vec2(1.1f, -1.2f)), icon_scale, ModelHandler::getModelById(11), 0.0f, icon_offset);
	this->title = new Label(title, MathHelper::glfwToTextCoord(this->icon->position + (this->icon->scale * Vec2(1.1f, .35f)), { 1.0f, 1.0f }), FontHandler::getFont("Merriweather-Black", 12.0f));
	this->price = new Label(Formatter::formatCookies(this->cost), MathHelper::glfwToTextCoord(this->icon->position + (this->scale * Vec2(1.75f, 0.2f)), { 1.0f, 1.0f }), FontHandler::getFont("Merriweather-Black", 13.0f), { 0.0f, 1.0f, 0.0f, 1.0f }, TextRenderer::Alignment::Right);
	this->label = new Label("[Upgrade]", MathHelper::glfwToTextCoord(this->icon->position + (this->icon->scale * Vec2(1.1f, -.2f)), { 1.0f, 1.0f }), FontHandler::getFont("Merriweather-Black", 10.0f));
	this->description = new Label(description, MathHelper::glfwToTextCoord(this->icon->position - Vec2(this->icon->scale.x - .03f, .07f), { 1.0f, 1.0f }), FontHandler::getFont("Merriweather-Black", 10.0f), { 1.0f, 1.0f, 1.0f, 1.0f }, TextRenderer::Alignment::Left, 250.0f);
	this->money_icon = new StaticImage((MathHelper::textToGLFWCoord(this->price->position - Vec2(this->price->font->getWidth(Formatter::formatCookies(this->cost, 3)), 0.0f)) - Vec2(-.04f, 1.5f * .0175f)), Vec2(.0175f, .0175f), ModelHandler::getModelById(8));

	this->borders.push_back(new StaticImage(this->position - (this->scale * Vec2(1.0f, 0.0f)), { .01375f, this->scale.y }, ModelHandler::getModelById(14)));
	this->borders.push_back(new StaticImage(this->position - (this->scale * Vec2(-1.0f, 0.0f)), { .01375f, this->scale.y }, ModelHandler::getModelById(14)));
	this->borders.push_back(new StaticImage(this->position - (this->scale * Vec2(0.0f, 1.0f)), { .01375f, this->scale.x * 1.04f }, ModelHandler::getModelById(9), 90.0f));
	this->borders.push_back(new StaticImage(this->position - (this->scale * Vec2(0.0f, -1.0f)), { .01375f, this->scale.x * 1.04f }, ModelHandler::getModelById(9), 90.0f));

}

UpgradeInfoPane::~UpgradeInfoPane() {

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

void UpgradeInfoPane::setPos(Vec2 position) {

	Vec2 old_pos = this->position;
	Vec2 diff = position - this->position;

	this->position += diff;
	this->icon->position += diff;
	this->money_icon->position += diff;

	this->title->position = MathHelper::glfwToTextCoord(this->icon->position + (this->icon->scale * Vec2(1.1f, .35f)), { 1.0f, 1.0f });
	this->price->position = MathHelper::glfwToTextCoord(this->icon->position + (this->scale * Vec2(1.75f, 0.2f)), { 1.0f, 1.0f });
	this->label->position = MathHelper::glfwToTextCoord(this->icon->position + (this->icon->scale * Vec2(1.1f, -.2f)), { 1.0f, 1.0f });
	this->description->position = MathHelper::glfwToTextCoord(this->icon->position - Vec2(this->icon->scale.x - .03f, .07f), { 1.0f, 1.0f });

	for (auto& panel : this->borders) {

		panel->position += diff;

	}

}

void UpgradeInfoPane::update() {

	if (!this->can_show) {

		this->make_invisible();

	}

	if (PlayerData::cookies >= this->cost) {

		this->price->color = { .4f, 1.0f, .4f, 1.0f };

	} else {

		this->price->color = { 1.0f, .4f, .4f, 1.0f };

	}

}

void UpgradeInfoPane::make_visible() {

	if (!this->visible && this->can_show) {

		this->visible = true;

		renderer->info_pane_renderer.addUpgradeInfoPane(this);

	}

}

void UpgradeInfoPane::make_invisible() {

	if (this->visible) {

		this->visible = false;

		auto& arr = renderer->info_pane_renderer.upgrade_info_panes;

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