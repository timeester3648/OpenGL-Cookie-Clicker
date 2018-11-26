#pragma once

#include "../../header/shop/Upgrade.h"

#include <glm\glm.hpp>
#include <vector>
#include <map>
#include <string>

typedef glm::vec2 Vec2;

class UpgradeHandler {

	friend class UpgradeLoader;

	private:

		struct UpgradeData {

			short id;
			std::string name;
			double cost;

			struct Description {

				std::string name;
				std::string lore;

			} description;

			Vec2 offset;

			std::map<short, unsigned long long> unlock_requirements;

		};

	public:

		static std::vector<UpgradeData> loaded_upgrades;
		static std::vector<Upgrade*> upgrades;
		static std::vector<short> unlocked_ids;
		static bool expanded_upgrades;
		static bool go_sort;

	public:

		static void update_upgrades();
		static void update();
		static void shift();
		static void sort(bool bypass = false);
		static void addUpgrade(short id, std::string name, std::string description, std::string lore, long double cost, Vec2 icon_offset);
		static void deleteUpgrade(Upgrade* upgrade);

		static unsigned long long has(std::vector<short> ids);
		static bool has(short id);

};