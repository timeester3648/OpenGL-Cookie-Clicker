#pragma once

#include <vector>
#include <string>

class CookieHandler {

	public:

		static long double cps[15];

	public:

		static long double process_cps(int index, long double cps_multiplied);
		static long double get_main_cps();
		static long double get_mouse_click();

		static void update();
		static void init();
	
};