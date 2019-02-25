#include "../../header/shop/ShopTile.h"
#include "../../header/handler/ModelHandler.h"
#include "../../header/handler/MouseHandler.h"
#include "../../header/handler/FontHandler.h"
#include "../../header/handler/ShopHandler.h"
#include "../../header/handler/UpgradeHandler.h"
#include "../../header/handler/InteractableHandler.h"
#include "../../header/display/DisplayManager.h"
#include "../../header/util/MathHelper.h"
#include "../../header/shop/ShopPrices.h"
#include "../../header/util/Formatter.h"
#include "../../header/game/PlayerData.h"
#include "../../header/game/GameSettings.h"
#include "../../header/handler/CookieHandler.h"
#include "../../header/Main.h"

#define EOUL_USE_GLFW_INPUT

#include <EOUL\Maths.h>
#include <EOUL\Utils.h>
#include <iostream>

using namespace EOUL::Math;
using namespace EOUL::Util;

ShopTile::ShopTile(std::string name, int index, bool locked) : ImageButton({ .84 + (.07f - .01875f * .5f) * 2.0f * .75f, .35f - index * .14f - .14f }, { .35f, .07f }, ModelHandler::getModelById(5)), name(std::move(name)), index(index), locked(locked) {

	this->mixIntensity = .15f;

	this->offset = { 0, this->index % 4 };

	int tmp = this->index;

	if (tmp >= 2) {

		tmp++;

	}

	for (int i = 1; i <= 4; i++) {

		std::string name = "buy" + std::to_string(i);
		Sound* sound = new Sound(name);

		sound->setGain(.05f);

		this->sounds.push_back(sound);

	}

	Vec2 window_pos = MathHelper::glfwToWindowCoord({ .634f + (.07f - .01875f * .5f) * 2.0f * .75f, .35f - index * .14f - .01f - .14f }, { .35f, .07f });

	window_pos.y = DisplayManager::height - window_pos.y;

	this->overlay = new StaticImage(this->position, this->scale, ModelHandler::getModelById(6));
	this->icon = new StaticImage(this->position - Vec2(.35f * .8f, 0.0f), Vec2(.07f, .07f), ModelHandler::getModelById(7), 0.0f, { 0, tmp });
	this->money_icon = new StaticImage(Vec2(.65f + (.07f - .01875f * .5f) * 2.0f * .75f, .35f - index * .14f - .035f - .14f), Vec2(.0175f, .0175f), ModelHandler::getModelById(8));
	this->name_label = new Label((this->locked ? "???" : this->name), window_pos, FontHandler::getFont("Merriweather-Bold", this->index != 12 ? 33.0f : 20.0f));
	this->money_label = new Label(Formatter::formatCookies(ShopPrices::getPrice(this->index), 3), window_pos + Vec2(20.0f, -15.0f), FontHandler::getFont("Merriweather-Black", 12.0f), { 0.0f, 1.0f, 0.0f, 1.0f });
	this->amount_label = new Label(*PlayerData::amounts[this->index] == 0 ? "" : Formatter::formatCookies((long double) *PlayerData::amounts[this->index], 0) + " ", window_pos + Vec2(200.0f, -7.5f), FontHandler::getFont("Merriweather-Bold", 33.0f), { 0.0f, 0.0f, 0.0f, .3f }, TextRenderer::Alignment::Right);

	this->info_pane = new BuildingInfoPane(name, "+" + std::to_string(*PlayerData::amounts[this->index]) + "cps, currently " + std::to_string(PlayerData::percentage(this->index)) + "% of all time", this->icon->offset, this->index);
	this->info_pane->setPos({ this->info_pane->position.x, this->position.y });

	renderer->static_image_renderer.addOverlay(this->icon);
	renderer->static_image_renderer.addOverlay(this->money_icon);
	renderer->text_renderer.addLabel(this->name_label);
	renderer->text_renderer.addLabel(this->money_label);
	renderer->text_renderer.addLabel(this->amount_label);

}

ShopTile::~ShopTile() {

	for (auto& sound : this->sounds) {

		delete sound;

	}

	delete this->overlay;
	delete this->icon;
	delete this->money_icon;
	delete this->name_label;
	delete this->money_label;
	delete this->amount_label;
	delete this->info_pane;

}

void ShopTile::play_random() {

	Sound* chosen = random(this->sounds);

	chosen->stop();
	chosen->play();

}

void ShopTile::onMouseUp(int key) {

	if (key == GLFW_MOUSE_BUTTON_LEFT) {

		if (this->mouse_down) {

			this->activate();
			
		}

		this->mouse_down = false;

	}

}

void ShopTile::scroll(float amount) {

	this->position.y += amount;
	this->overlay->position.y += amount;
	this->icon->position.y += amount;
	this->money_icon->position.y += amount;

	Vec2 window_pos = MathHelper::glfwToWindowCoord({ .634f + (.07f - .01875f * .5f) * 2.0f * .75f, this->position.y - .01f }, { .35f, .07f });

	window_pos.y = DisplayManager::height - window_pos.y;

	this->name_label->position = window_pos;
	this->money_label->position = window_pos + Vec2(20.0f, -15.0f);
	this->amount_label->position = window_pos + Vec2(200.0f, -7.5f);

}

void ShopTile::setPos(Vec2 pos) {

	Vec2 diff = this->position - pos;

	this->position -= diff;
	this->overlay->position -= diff;
	this->icon->position -= diff;
	this->money_icon->position -= diff;

	Vec2 window_pos = MathHelper::glfwToWindowCoord({ .634f + (.07f - .01875f * .5f) * 2.0f * .75f, this->position.y - .01f }, { .35f, .07f });

	window_pos.y = DisplayManager::height - window_pos.y;

	this->name_label->position = window_pos;
	this->money_label->position = window_pos + Vec2(20.0f, -15.0f);
	this->amount_label->position = window_pos + Vec2(200.0f, -7.5f);

	this->info_pane->setPos({ this->info_pane->position.x, this->position.y });

}

void ShopTile::activate() {

	size_t amount = 1;

	if (isKeyDown(DisplayManager::window, GLFW_KEY_LEFT_CONTROL)) {

		amount = 10;

	} else if (isKeyDown(DisplayManager::window, GLFW_KEY_LEFT_SHIFT)) {

		amount = 100;

	}

	if (PlayerData::cookies < ShopPrices::getPrice(this->index, amount)) {

		return;

	} else {

		PlayerData::cookies -= ShopPrices::getPrice(this->index, amount);

	}

	(*PlayerData::amounts[this->index]) += amount;

	this->money_label->text = Formatter::formatCookies(ShopPrices::getPrice(this->index), 3);
	this->amount_label->text = (*PlayerData::amounts[this->index] == 0 ? "" : Formatter::formatCookies((long double) *PlayerData::amounts[this->index], 0)) + " ";

	this->play_random();

	UpgradeHandler::update_upgrades();

}

void ShopTile::update() {

	size_t amount = 1;

	if (isKeyDown(DisplayManager::window, GLFW_KEY_LEFT_CONTROL)) {

		amount = 10;

	} else if (isKeyDown(DisplayManager::window, GLFW_KEY_LEFT_SHIFT)) {

		amount = 100;

	}

	this->info_pane->description->text = "+" + Formatter::formatCookies(CookieHandler::process_cps(this->index, CookieHandler::cps[this->index])) + " cps, currently " + Formatter::formatCookies(PlayerData::percentage(this->index), 2) + "% of all time";
	this->info_pane->price->text = Formatter::formatCookies(ShopPrices::getPrice(this->index, amount), 3);

	this->info_pane->update();

	this->locked = ShopHandler::locked[this->index];

	if (!this->locked) {

		this->icon->offset = { 0, this->icon->offset.y };
		this->name_label->text = this->name;
		this->doMixColor = false;
		this->mixColor = { 1.0f, 1.0f, 1.0f, 1.0f };
		this->mixIntensity = .5f;

	} else {

		this->icon->offset = { 1, this->icon->offset.y };
		this->name_label->text = "???";
		this->doMixColor = true;
		this->mixColor = { 0, 0, 0, 1.0f };
		this->mixIntensity = .3f;

	}

	this->money_label->text = Formatter::formatCookies(ShopPrices::getPrice(this->index, amount), 3);

	if (PlayerData::cookies >= ShopPrices::getPrice(this->index, amount)) {

		this->money_label->color = { .4f, 1.0f, .4f, 1.0f };

	} else {

		this->money_label->color = { 1.0f, .4f, .4f, 1.0f };

	}

	if (!this->mouse_over && this->over(MouseHandler::mouseX, MouseHandler::mouseY)) {

		this->onMouseEnter();

	} else if (this->mouse_over && !this->over(MouseHandler::mouseX, MouseHandler::mouseY)) {

		this->onMouseLeave();

	}

	if (!this->locked) {

		this->doMixColor = this->mouse_over;

	}

	if (this->mouse_down && this->mouse_over && !added && PlayerData::cookies >= ShopPrices::getPrice(this->index)) {

		this->added = true;

		renderer->static_image_renderer.addOverlay(overlay);

	} else if (!this->mouse_down && added || !this->mouse_over && added) {

		this->added = false;

		for (auto& over : renderer->static_image_renderer.overlays) {

			if (over.first == ModelHandler::getModelById(6)) {

				size_t i = 0;
				for (auto& lay : over.second) {

					if (lay == this->overlay) {

						over.second.erase(over.second.begin() + i);

						break;

					}

					i++;

				}

			}

		}

	}

	if (this->over(MouseHandler::mouseX, MouseHandler::mouseY)) {

		glfwSetCursor(DisplayManager::window, hand);

	} else if (!InteractableHandler::over_any()) {

		glfwSetCursor(DisplayManager::window, arrow);

	}

}

void ShopTile::onMouseEnter() {

	this->mouse_over = true;

	this->info_pane->make_visible();

}

void ShopTile::onMouseLeave() {

	this->mouse_over = false;
	this->mouse_down = false;

	this->info_pane->make_invisible();

}