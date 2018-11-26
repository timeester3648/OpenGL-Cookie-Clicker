#pragma once

#include "../objects/StaticImage.h"
#include "../text/Label.h"

#include <glm\glm.hpp>
#include <vector>

typedef glm::vec2 Vec2;

class BuildingInfoPane : public StaticImage {

	public:

		StaticImage *icon = nullptr, *money_icon = nullptr;
		Label *title = nullptr, *description = nullptr, *price = nullptr, *label;
		std::vector<StaticImage*> borders;
		int index;
		bool visible = false;

	public:

		BuildingInfoPane(std::string title, std::string description, Vec2 icon_offset, int index);
		~BuildingInfoPane();

	public:

		void make_visible();
		void make_invisible();
		void update();
		
		void setPos(Vec2 position);

};