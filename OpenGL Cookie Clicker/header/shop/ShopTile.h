#pragma once

#include "../interactable/ImageButton.h"
#include "../ui/BuildingInfoPane.h"
#include "../objects/StaticImage.h"
#include "../text/Label.h"
#include "../sound/Sound.h"

#include <string>
#include <glm\glm.hpp>

typedef glm::vec2 Vec2;

class ShopTile : public ImageButton {

	public:

		std::string name;
		int index;
		std::vector<Sound*> sounds;
		BuildingInfoPane* info_pane = nullptr;
		StaticImage *icon = nullptr, *overlay = nullptr, *money_icon = nullptr;
		Label *name_label = nullptr, *money_label = nullptr, *amount_label = nullptr;

		bool added = false;
		bool locked;

	public:

		ShopTile(std::string name, int index, bool locked = false);
		~ShopTile();

	private:

		void play_random();

	public:

		virtual void onMouseUp(int key) override;

		virtual void activate() override;
		virtual void update() override;
		virtual void onMouseEnter() override;
		virtual void onMouseLeave() override;

		void scroll(float amount);
		void setPos(Vec2 pos);

};