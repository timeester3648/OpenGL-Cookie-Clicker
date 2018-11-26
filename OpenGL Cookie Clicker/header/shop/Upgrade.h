#pragma once

#include "../objects/StaticImage.h"
#include "../interactable/Button.h"
#include "../ui/UpgradeInfoPane.h"

#include <string>
#include <vector>

class Upgrade : public Button {

	friend class UpgradeHandler;

	public:

		short id;
		StaticImage* border;
		StaticImage* icon;
		StaticImage* shade;
		UpgradeInfoPane* info_pane;
		long double cost;
		std::string name;
		std::string description;
		std::string lore;
		bool other_row;
		bool added = false;
		bool enough = false;
		bool need_sort = true;
		int index;

		std::vector<Sound*> sounds;

	public:

		Upgrade(short id, Vec2 position, long double cost, Vec2 icon_offset, std::string name, std::string description, std::string lore, int index);
		~Upgrade();

	private:

		void removeOverlays();
		void addOverlays();
		void play_random();

	public:

		void scroll(float amount);
		void setPos(Vec2 pos);

		virtual void update() override;
		virtual void activate() override;
		virtual void onMouseEnter() override;
		virtual void onMouseLeave() override;

};