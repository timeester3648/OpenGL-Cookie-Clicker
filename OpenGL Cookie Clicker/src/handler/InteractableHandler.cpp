#include "../../header/handler/InteractableHandler.h"
#include "../../header/handler/UpgradeHandler.h"
#include "../../header/handler/MouseHandler.h"

std::vector<Interactable*> InteractableHandler::interactables;

void InteractableHandler::onMouseMove() {

	for (auto& interactable : interactables) {

		if (interactable->over(MouseHandler::mouseX, MouseHandler::mouseY)) {

			interactable->onMouseMove();

		}

	}

	for (auto& interactable : UpgradeHandler::upgrades) {

		if (interactable->over(MouseHandler::mouseX, MouseHandler::mouseY)) {

			interactable->onMouseMove();

		}

	}

}

void InteractableHandler::update() {

	for (auto& interactable : interactables) {

		interactable->update();

	}

}

bool InteractableHandler::over_any() {

	for (auto& interactable : interactables) {

		if (interactable->over(MouseHandler::mouseX, MouseHandler::mouseY)) {

			return true;

		}

	}

	for (auto& interactable : UpgradeHandler::upgrades) {

		if (interactable->over(MouseHandler::mouseX, MouseHandler::mouseY)) {

			return true;

		}

	}

	return false;

}

bool InteractableHandler::over_upgrades() {

	for (auto& interactable : UpgradeHandler::upgrades) {

		if (interactable->over(MouseHandler::mouseX, MouseHandler::mouseY)) {

			return true;

		}

	}

	return false;

}

void InteractableHandler::onMouseUp(int key) {

	for (auto& interactable : interactables) {

		if (interactable->over(MouseHandler::mouseX, MouseHandler::mouseY)) {

			interactable->onMouseUp(key);

		}

	}
	for (auto& interactable : UpgradeHandler::upgrades) {

		if (interactable->over(MouseHandler::mouseX, MouseHandler::mouseY)) {

			interactable->onMouseUp(key);

		}

	}


}

void InteractableHandler::onMouseDown(int key) {

	for (auto& interactable : interactables) {

		if (interactable->over(MouseHandler::mouseX, MouseHandler::mouseY)) {

			interactable->onMouseDown(key);

		}

	}

	for (auto& interactable : UpgradeHandler::upgrades) {

		if (interactable->over(MouseHandler::mouseX, MouseHandler::mouseY)) {

			interactable->onMouseDown(key);

		}

	}

}