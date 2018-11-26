#include "../../header/loading/UpgradeLoader.h"
#include "../../header/handler/UpgradeHandler.h"

#include <fstream>
#include <string>
#include <iostream>

#undef GetObject

rapidjson::Document UpgradeLoader::document;

void UpgradeLoader::load() {

	using UpgradeData = UpgradeHandler::UpgradeData;

	std::ifstream in("res/data/upgrades.json");
	std::string content;
	std::string line;

	while (getline(in, line)) {

		content += line + '\n';

	}

	document.Parse(content.c_str());

	auto upgrades = document["upgrades"].GetArray();

	for (auto& upgrade : upgrades) {
		
		auto requirements = upgrade["unlock-requirements"].GetArray();
		std::map<short, unsigned long long> unlock_requirements;

		for (auto& requirement : requirements) {

			unlock_requirements.insert(std::map<short, unsigned long long>::value_type(requirement["id"].GetUint(), requirement["amount"].GetUint64()));

		}

		UpgradeHandler::loaded_upgrades.push_back({ short(upgrade["id"].GetInt()), upgrade["name"].GetString(), upgrade["cost"].GetDouble(), { upgrade["description"].GetObject()["main"].GetString(), upgrade["description"].GetObject()["lore"].GetString() }, { float(upgrade["icon-offset"].GetObject()["x"].GetUint()), float(upgrade["icon-offset"].GetObject()["y"].GetUint()) }, unlock_requirements });

	}

}