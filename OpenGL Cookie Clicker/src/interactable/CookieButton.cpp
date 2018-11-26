#include "../../header/interactable/CookieButton.h"
#include "../../header/handler/ModelHandler.h"
#include "../../header/handler/MouseHandler.h"
#include "../../header/handler/EffectHandler.h"
#include "../../header/display/DisplayManager.h"
#include "../../header/handler/CookieHandler.h"
#include "../../header/handler/InteractableHandler.h"
#include "../../header/game/PlayerData.h"
#include "../../header/util/MathHelper.h"

#include <iostream>
#include <EOUL\Maths.h>
#include <isect2d\isect2d.h>
#include <glm\glm.hpp>
#include <filesystem>

typedef isect2d::AABB<glm::vec2> AABB;

using namespace EOUL::Math;

CookieButton::CookieButton(Vec2 position, Vec2 scale) : ImageButton(position, scale, ModelHandler::getModelById(0)) {

	this->start_dim = this->scale;

	for (int i = 1; i <= 7; i++) {

		std::string name = "clickb" + std::to_string(i);
		Sound* sound = new Sound(name);

		sound->setGain(.05f);

		this->sounds.push_back(sound);

	}

}

CookieButton::~CookieButton() {

	for (auto& sound : this->sounds) {

		delete sound;

	}

}

void CookieButton::activate() {

	PlayerData::cookies += CookieHandler::get_mouse_click();
	PlayerData::cookies_produced += CookieHandler::get_mouse_click();

}

void CookieButton::play_random() {

	Sound* chosen = random(this->sounds);

	chosen->stop();
	chosen->play();

}

void CookieButton::update() {

	if (!this->mouse_over && this->over(MouseHandler::mouseX, MouseHandler::mouseY)) {

		this->onMouseEnter();

	} else if (this->mouse_over && !this->over(MouseHandler::mouseX, MouseHandler::mouseY)) {

		this->onMouseLeave();

	}

	if (this->over(MouseHandler::mouseX, MouseHandler::mouseY)) {

		glfwSetCursor(DisplayManager::window, hand);

		if (this->mouse_down) {

			this->scale = this->start_dim * .9f;

		}

	} else if (!InteractableHandler::over_any()) {

		glfwSetCursor(DisplayManager::window, arrow);

	}

	if (!this->mouse_over || !this->mouse_down) {

		this->scale = this->start_dim;

	}

}

void CookieButton::onMouseDown(int key) {

	if (key == GLFW_MOUSE_BUTTON_LEFT) {

		this->mouse_down = true;

		this->play_random();

	}

}

void CookieButton::onMouseUp(int key) {

	if (key == GLFW_MOUSE_BUTTON_LEFT) {

		if (this->mouse_down) {

			this->activate();
			this->play_random();

			EffectHandler::addClickLabel();

		}

		this->mouse_down = false;

	}

}

bool CookieButton::over(double x, double y) {

	Vec2 tmp_scl = this->scale;

	tmp_scl.y *= -1;

	Vec2 pos = MathHelper::glfwToWindowCoord(this->position, this->scale);
	Vec2 top_left = MathHelper::glfwToWindowCoord(this->position - tmp_scl, this->scale);
	Vec2 bottom_right = MathHelper::glfwToWindowCoord(this->position + tmp_scl, this->scale);

	return (x >= top_left.x && x <= bottom_right.x) && (y >= top_left.y && y <= bottom_right.y) && dist(x, y, pos.x, pos.y) < 87;

}