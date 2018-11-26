#include "../../header/shop/Shop.h"
#include "../../header/shop/ShopPrices.h"
#include "../../header/handler/ShopHandler.h"
#include "../../header/Main.h"

std::vector<ShopTile*> Shop::tiles;

void Shop::init() {

	ShopPrices::init();

	bool did_c = false;
	bool did_g = false;

	if (!ShopHandler::registered[0]) {

		registerTile(0);

		ShopHandler::registered[0] = true;
		ShopHandler::to_be_registered[0] = false;
		ShopHandler::locked[0] = true;

		did_c = true;

	}

	if (!ShopHandler::registered[1]) {

		registerTile(1);

		ShopHandler::registered[1] = true;
		ShopHandler::to_be_registered[1] = false;
		ShopHandler::locked[0] = true;

		did_g = true;

	}

	for (int i = 0; i < sizeof(ShopHandler::registered); i++) {

		if (!ShopHandler::registered[i] || i == 0 && did_c || i == 1 && did_g) {

			continue;

		}

		switch (i) {

			case 0:

				registerTile("Cursor");

				break;

			case 1:

				registerTile("Grandma");

				break;

			case 2:

				registerTile("Farm", ShopHandler::locked[i]);

				break;

			case 3:

				registerTile("Mine", ShopHandler::locked[i]);

				break;

			case 4:

				registerTile("Factory", ShopHandler::locked[i]);

				break;

			case 5:

				registerTile("Bank", ShopHandler::locked[i]);

				break;

			case 6:

				registerTile("Temple", ShopHandler::locked[i]);

				break;

			case 7:

				registerTile("Wizard Tower", ShopHandler::locked[i]);

				break;

			case 8:

				registerTile("Shipment", ShopHandler::locked[i]);

				break;

			case 9:

				registerTile("Alchemy Lab", ShopHandler::locked[i]);

				break;

			case 10:

				registerTile("Portal", ShopHandler::locked[i]);

				break;

			case 11:

				registerTile("Time Machine", ShopHandler::locked[i]);

				break;

			case 12:

				registerTile("Antimatter Condenser", ShopHandler::locked[i]);

				break;

			case 13:

				registerTile("Prism", ShopHandler::locked[i]);

				break;

			case 14:

				registerTile("Chancemaker", ShopHandler::locked[i]);

				break;

			default:

				throw std::runtime_error("Wtf, Is You DUMB?");

		}

	}

}

void Shop::update() {

	for (int i = 0; i < sizeof(ShopHandler::to_be_registered); i++) {

		if (!ShopHandler::to_be_registered[i]) {

			continue;

		}

		ShopHandler::registered[i] = true;
		ShopHandler::to_be_registered[i] = false;

		switch (i) {

			case 0:

				registerTile("Cursor", true);

				break;

			case 1:

				registerTile("Grandma", true);

				break;

			case 2:

				registerTile("Farm", true);

				break;

			case 3:

				registerTile("Mine", true);

				break;

			case 4:

				registerTile("Factory", true);

				break;

			case 5:

				registerTile("Bank", true);

				break;

			case 6:

				registerTile("Temple", true);

				break;

			case 7:

				registerTile("Wizard Tower", true);

				break;

			case 8:

				registerTile("Shipment", true);

				break;

			case 9:

				registerTile("Alchemy Lab", true);

				break;

			case 10:

				registerTile("Portal", true);

				break;

			case 11:

				registerTile("Time Machine", true);

				break;

			case 12:

				registerTile("Antimatter Condenser", true);

				break;

			case 13:

				registerTile("Prism", true);

				break;

			case 14:

				registerTile("Chancemaker", true);

				break;

			default:

				throw std::runtime_error("Wtf, Is You DUMB?");

		}

	}

}

void Shop::registerTile(int index) {

	switch (index) {

		case 0:

			registerTile("Cursor", true);

			break;

		case 1:

			registerTile("Grandma", true);

			break;

		case 2:

			registerTile("Farm", true);

			break;

		case 3:

			registerTile("Mine", true);

			break;

		case 4:

			registerTile("Factory", true);

			break;

		case 5:

			registerTile("Bank", true);

			break;

		case 6:

			registerTile("Temple", true);

			break;

		case 7:

			registerTile("Wizard Tower", true);

			break;

		case 8:

			registerTile("Shipment", true);

			break;

		case 9:

			registerTile("Alchemy Lab", true);

			break;

		case 10:

			registerTile("Portal", true);

			break;

		case 11:

			registerTile("Time Machine", true);

			break;

		case 12:

			registerTile("Antimatter Condenser", true);

			break;

		case 13:

			registerTile("Prism", true);

			break;

		case 14:

			registerTile("Chancemaker", true);

			break;

		default:

			throw std::runtime_error("Wtf, Is You DUMB?");

	}

}

void Shop::registerTile(std::string name, bool locked) {

	static int index = 0;

	ShopTile* tile = new ShopTile(name, index, locked);

	tiles.push_back(tile);
	renderer->button_renderer.addImageButton(tile);

	index++;

}