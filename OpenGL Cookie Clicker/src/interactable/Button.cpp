#include "../../header/interactable/Button.h"
#include "../../header/display/DisplayManager.h"
#include "../../header/handler/MouseHandler.h"
#include "../../header/handler/InteractableHandler.h"

#include <iostream>

GLFWcursor* Button::arrow = nullptr;
GLFWcursor* Button::hand = nullptr;

Button::Button(Vec2 position, Vec2 scale) : Interactable(position, scale) {

	if (!arrow || !hand) {

		arrow = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
		hand = glfwCreateStandardCursor(GLFW_HAND_CURSOR);

	}

}

void Button::update() {

	if (!this->mouse_over && this->over(MouseHandler::mouseX, MouseHandler::mouseY)) {

		this->onMouseEnter();

	} else if (this->mouse_over && !this->over(MouseHandler::mouseX, MouseHandler::mouseY)) {

		this->onMouseLeave();

	}

	if (this->over(MouseHandler::mouseX, MouseHandler::mouseY)) {

		glfwSetCursor(DisplayManager::window, hand);

	} else if (!InteractableHandler::over_any()) {

		glfwSetCursor(DisplayManager::window, arrow);

	}

}

void Button::onMouseDown(int key) {

	if (key == GLFW_MOUSE_BUTTON_LEFT) {

		this->mouse_down = true;

	}

}

void Button::onMouseUp(int key) {

	if (key == GLFW_MOUSE_BUTTON_LEFT) {

		if (this->mouse_down) {

			this->activate();

			if (this->sound != nullptr) {

				this->sound->play();

			}

		}

		this->mouse_down = false;

	}

}

void Button::onMouseEnter() {

	this->mouse_over = true;

}

void Button::onMouseLeave() {

	this->mouse_over = false;
	this->mouse_down = false;

}