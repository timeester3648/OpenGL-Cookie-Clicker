#pragma once

class ShopHandler {

	public:

		static bool registered[15];
		static bool to_be_registered[15];
		static bool locked[15];

		static float total_scroll;

	public:

		static void init();
		static void update();
		static void scroll(float offset);

};