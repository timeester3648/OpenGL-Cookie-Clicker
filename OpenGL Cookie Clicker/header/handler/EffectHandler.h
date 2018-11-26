#pragma once

#include "../../header/effects/ClickLabel.h"
#include "../../header/handler/CookieHandler.h"

#include <vector>

class EffectHandler {

	public:

		static std::vector<ClickLabel*> click_labels;
		static constexpr size_t max_size = 10;

	public:

		static void update();
		static void addClickLabel();

};