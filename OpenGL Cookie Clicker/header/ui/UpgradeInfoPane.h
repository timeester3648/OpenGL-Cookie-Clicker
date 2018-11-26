#pragma once

#include "../objects/StaticImage.h"
#include "../text/Label.h"

#include <glm\glm.hpp>
#include <vector>

typedef glm::vec2 Vec2;

class UpgradeInfoPane : public StaticImage {

	public:

		StaticImage *icon = nullptr, *money_icon = nullptr;
		Label *title = nullptr, *description = nullptr, *price = nullptr, *label;
		std::vector<StaticImage*> borders;
		long double cost;
		bool visible = false, can_show;

	public:

		UpgradeInfoPane(std::string title, std::string description, std::string lore, long double cost, Vec2 icon_offset);
		~UpgradeInfoPane();

	public:

		void make_visible();
		void make_invisible();
		void update();
		
		void setPos(Vec2 position);

};