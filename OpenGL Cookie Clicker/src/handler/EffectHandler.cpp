#include "../../header/handler/EffectHandler.h"
#include "../../header/util/Formatter.h"
#include "../../header/handler/MouseHandler.h"
#include "../../header/game/PlayerData.h"
#include "../../header/handler/FontHandler.h"
#include "../../header/handler/CookieHandler.h"
#include "../../header/display/DisplayManager.h"
#include "../../header/Main.h"

#include <EOUL\Maths.hpp>
#include <iostream>

using namespace EOUL::Math;

std::vector<ClickLabel*> EffectHandler::click_labels;

void EffectHandler::update() {

	static float speed = .75f;
	static float alpha_degredation = .01f;

	for (size_t i = click_labels.size() - 1; i >= 0 && i != -1; i--) {

		if (click_labels[i]->color.a <= 0.0) {

			delete click_labels[i];

			click_labels.erase(click_labels.begin() + i);

			continue;

		}

		click_labels[i]->position.y += speed;
		click_labels[i]->color.a -= alpha_degredation;

	}

}

void EffectHandler::addClickLabel() {

	if (max_size >= click_labels.size() + 1) {

		click_labels.insert(click_labels.begin(), new ClickLabel());

	} else {

		ClickLabel* label = click_labels[click_labels.size() - 1];

		click_labels.pop_back();

		label->text = "+" + Formatter::formatCookies(CookieHandler::get_mouse_click()); 
		label->position = { MouseHandler::mouseX + random(-20.0f, 20.0f), DisplayManager::height - MouseHandler::mouseY };
		label->color = { 1.0f, 1.0f, 1.0f, 1.0f };

		click_labels.insert(click_labels.begin(), label);

	}

}