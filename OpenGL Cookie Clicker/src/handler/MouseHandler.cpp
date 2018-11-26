#include "../../header/handler/MouseHandler.h"
#include "../../header/handler/ShopHandler.h"
#include "../../header/display/DisplayManager.h"
#include "../../header/util/MathHelper.h"
#include "../../header/handler/InteractableHandler.h"

#include <iostream>

bool MouseHandler::leftMouseDown = false;
bool MouseHandler::rightMouseDown = false;
double MouseHandler::mouseX = 0, MouseHandler::mouseY = 0;

void MouseHandler::onMouseMove() {

	InteractableHandler::onMouseMove();

}

void MouseHandler::mouse_move_callback(GLFWwindow* window, double x, double y) {

	mouseX = x;
	mouseY = y;

	onMouseMove();

}

void MouseHandler::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {

	Vec2 pos = MathHelper::glfwToWindowCoord({ .84 - .35f, .35f }, { .35f, .07f });

	if (mouseX > pos.x) {

		ShopHandler::scroll(yoffset);

	}

}

void MouseHandler::mouse_input_callback(GLFWwindow* window, int button, int action, int mods) {

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {

		leftMouseDown = true;

	} else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {

		leftMouseDown = false;

	}

	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {

		rightMouseDown = true;

	} else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE) {

		rightMouseDown = false;

	}

	if (action == GLFW_PRESS) {

		InteractableHandler::onMouseDown(button);

	} else if (action == GLFW_RELEASE) {

		InteractableHandler::onMouseUp(button);

	}

}