#include "../../header/handler/ShopHandler.h"
#include "../../header/handler/UpgradeHandler.h"
#include "../../header/shop/ShopPrices.h"
#include "../../header/game/PlayerData.h"
#include "../../header/game/GameSettings.h"
#include "../../header/display/DisplayManager.h"
#include "../../header/shop/Shop.h"
#include "../../header/util/MathHelper.h"
#include "../../header/Main.h"

#include <iostream>
#include <EOUL\Maths.h>

bool ShopHandler::registered[15];
bool ShopHandler::to_be_registered[15];
bool ShopHandler::locked[15];
float ShopHandler::total_scroll = 0.0f;

using namespace EOUL::Math;

void ShopHandler::init() {

	memset(&registered, false, sizeof(registered));
	memset(&to_be_registered, false, sizeof(to_be_registered));
	memset(&locked, true, sizeof(locked));

}

void ShopHandler::scroll(float offset) {

	if (!registered[6] || UpgradeHandler::expanded_upgrades && UpgradeHandler::upgrades.size() > 5) {

		return;

	}

	float initial_add = (-1 * offset) / DisplayManager::height * GameSettings::scroll_speed;
	float label_add = (-1 * offset) * GameSettings::scroll_speed;

	total_scroll += initial_add;

	int max_index = 0;
	ShopTile* highest = nullptr;
	ShopTile* lowest = nullptr;

	for (auto& tile : Shop::tiles) {

		max_index = max(max_index, tile->index);

	}

	for (auto& tile : Shop::tiles) {

		if (tile->index == max_index) {

			lowest = tile;

		} else if (tile->index == 0) {

			highest = tile;

		}

	}

	for (auto& tile : Shop::tiles) {

		tile->scroll(initial_add);

	}

	for (auto& upgrade : UpgradeHandler::upgrades) {

		upgrade->scroll(initial_add);

	}

	panel_2->position.y += initial_add;
	panel_3->position.y += initial_add;
	shop_label->position.y += label_add;
	shop_gradient_top->position.y += initial_add;

	Vec2 window_pos = MathHelper::glfwToWindowCoord(lowest->position - Vec2(0, lowest->scale.y), lowest->scale);

	while (total_scroll < 0 || window_pos.y < DisplayManager::height) {

		for (auto& tile : Shop::tiles) {

			tile->scroll(-initial_add / 10);

		}

		total_scroll -= initial_add / 10;
		panel_2->position.y -= initial_add / 10;
		panel_3->position.y -= initial_add / 10;
		shop_label->position.y -= label_add / 10;
		shop_gradient_top->position.y -= initial_add / 10;

		for (auto& upgrade : UpgradeHandler::upgrades) {

			upgrade->scroll(-initial_add / 10);

		}

		window_pos = MathHelper::glfwToWindowCoord(lowest->position - Vec2(0, lowest->scale.y), lowest->scale);

	}

}

void ShopHandler::update() {

	auto check = [&](size_t index) {

		return index + 1 < sizeof(locked);

	};

	for (size_t i = sizeof(locked) - 1; i >= 0 && i != -1; i--) {

		if (PlayerData::cookies >= ShopPrices::getPrice((int) i)) {

			locked[i] = false;

			if (check(i)) {

				if (!registered[i + 1]) {

					to_be_registered[i + 1] = true;

				}

				if (check(i + 1)) {

					if (!registered[i + 2]) {

						to_be_registered[i + 2] = true;
						
					}

				}

				break;

			}

		}

	}

	Shop::update();

}