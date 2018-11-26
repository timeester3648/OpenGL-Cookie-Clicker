#pragma once

#include "../interfaces/Interactable.h"

#include <vector>

class InteractableHandler {

	public:

		static std::vector<Interactable*> interactables;

	public:

		static bool over_any();
		static bool over_upgrades();

		static void update();
		static void onMouseMove();

		static void onMouseUp(int key);
		static void onMouseDown(int key);

};