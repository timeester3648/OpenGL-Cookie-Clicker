#include "../../header/shop/Upgrade.h"
#include "../../header/handler/ModelHandler.h"
#include "../../header/handler/UpgradeHandler.h"
#include "../../header/handler/MouseHandler.h"
#include "../../header/handler/InteractableHandler.h"
#include "../../header/game/PlayerData.h"
#include "../../header/Main.h"

#include <iostream>
#include <EOUL\Maths.hpp>

using namespace EOUL::Math;

Upgrade::Upgrade(short id, Vec2 position, long double cost, Vec2 icon_offset, std::string name, std::string description, std::string lore, int index) : Button(position, { .07f - .01875f * .5f, .07f - .01875f * .5f }), id(id), cost(cost), name(std::move(name)), description(std::move(description)), lore(std::move(lore)), index(index), other_row(index >= 5) {

	this->enough = PlayerData::cookies >= cost;
	this->shade = new StaticImage(position, { .07f - .01875f * .5f, .07f - .01875f * .5f }, ModelHandler::getModelById(3), 0.0f);
	this->icon = new StaticImage(position, { .07f - .01875f * .5f, .07f - .01875f * .5f }, ModelHandler::getModelById(11), 0.0f, icon_offset);
	this->border = new StaticImage(position, { .07f - .01875f * .5f, .07f - .01875f * .5f }, ModelHandler::getModelById(12), 0.0f, { (PlayerData::cookies >= cost ? 0 : 1), 0 });
	this->info_pane = new UpgradeInfoPane(name, description, lore, cost, icon_offset);

	this->info_pane->can_show = ((this->other_row && UpgradeHandler::expanded_upgrades) || !this->other_row);
	this->info_pane->setPos({ this->info_pane->position.x, this->position.y - this->scale.y });
	
	if (!this->other_row) {

		this->addOverlays();

	}

	for (int i = 1; i <= 4; i++) {

		std::string name = "buy" + std::to_string(i);
		Sound* sound = new Sound(name);

		sound->setGain(.05f);

		this->sounds.push_back(sound);

	}

}

Upgrade::~Upgrade() {

	this->removeOverlays();

	delete this->shade;
	delete this->icon;
	delete this->border;
	delete this->info_pane;

}

void Upgrade::play_random() {

	Sound* chosen = random(this->sounds);

	chosen->stop();
	chosen->play();

}

void Upgrade::scroll(float amount) {

	this->position.y += amount;
	this->shade->position.y += amount;
	this->icon->position.y += amount;
	this->border->position.y += amount;

	this->info_pane->setPos({ this->info_pane->position.x, this->position.y - this->scale.y });

}

void Upgrade::setPos(Vec2 pos) {

	this->position = pos;

	this->icon->position = pos;
	this->shade->position = pos;
	this->border->position = pos;

	this->info_pane->setPos({ this->info_pane->position.x, this->position.y - this->scale.y });

}

void Upgrade::activate() {

	if (PlayerData::cookies < this->cost) {

		return;

	} else {

		this->play_random();

		PlayerData::cookies -= this->cost;

	}

	UpgradeHandler::unlocked_ids.push_back(this->id);
	UpgradeHandler::deleteUpgrade(this);

}

void Upgrade::update() {

	this->info_pane->can_show = ((this->other_row && UpgradeHandler::expanded_upgrades) || !this->other_row);
	this->info_pane->update();

	this->border->offset = { (PlayerData::cookies >= cost ? 0 : 1), 0 };

	if (this->enough && PlayerData::cookies < cost) {

		this->enough = false;
		this->need_sort = true;

	} else if (!this->enough && PlayerData::cookies >= cost) {

		this->enough = true;
		this->need_sort = true;

	}

	if (!this->mouse_over && this->over(MouseHandler::mouseX, MouseHandler::mouseY)) {

		this->onMouseEnter();

	} else if (this->mouse_over && !this->over(MouseHandler::mouseX, MouseHandler::mouseY)) {

		this->onMouseLeave();

	}

	bool mouse = this->over(MouseHandler::mouseX, MouseHandler::mouseY);

	if (mouse && UpgradeHandler::expanded_upgrades || mouse && !UpgradeHandler::expanded_upgrades && !this->other_row) {

		glfwSetCursor(DisplayManager::window, hand);

		UpgradeHandler::expanded_upgrades = true;

		this->info_pane->make_visible();

	} else if (!InteractableHandler::over_any()) {

		glfwSetCursor(DisplayManager::window, arrow);

	}

	if (!InteractableHandler::over_upgrades()) {

		UpgradeHandler::expanded_upgrades = false;

	}

	if (UpgradeHandler::expanded_upgrades && !this->added && this->other_row) {

		this->addOverlays();

		this->added = true;

	} else if (!UpgradeHandler::expanded_upgrades && this->added && this->other_row) {

		this->removeOverlays();

		this->added = false;

	}

}

void Upgrade::removeOverlays() {

	size_t i = 0;
	for (auto& it : renderer->static_image_renderer.overlays) {

		for (auto& overlay : it.second) {

			if (overlay == this->shade || overlay == this->icon || overlay == this->border) {

				it.second.erase(it.second.begin() + i);

			}

			i++;

		}

		i = 0;

	}

}

void Upgrade::addOverlays() {
	
	renderer->static_image_renderer.addOverlay(this->shade);
	renderer->static_image_renderer.addOverlay(this->icon);
	renderer->static_image_renderer.addOverlay(this->border);

}

void Upgrade::onMouseEnter() {

	this->mouse_over = true;

	this->info_pane->make_visible();

}

void Upgrade::onMouseLeave() {

	this->mouse_over = false;
	this->mouse_down = false;

	this->info_pane->make_invisible();

}