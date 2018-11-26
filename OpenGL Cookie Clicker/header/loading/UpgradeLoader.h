#pragma once

#undef max
#undef min
#include <rapidjson\document.h>

class UpgradeLoader {

	public:

		static rapidjson::Document document;

	public:

		static void load();

};