#pragma once

#include <string>

class GameSaver {

	private:

		static std::string path;

	public:

		static void load_game();
		static void save_game();

		static void loop();

};