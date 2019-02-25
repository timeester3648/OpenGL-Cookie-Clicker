#pragma once

#include "../display/DisplayManager.h"

#include <glm\glm.hpp>

typedef glm::vec2 Vec2;

/*

	* Choose which functions you want to override, all functions are optional
	* Not a traditional interface, but it still is an interface

*/
class Interactable {

	public:

		Vec2 position, scale;

	public:

		Interactable(Vec2 position, Vec2 scale);

	public:

		virtual void update() = 0;

		virtual void onKeyDown(int key);
		virtual void onKeyUp(int key);

		virtual void onMouseDown(int key);
		virtual void onMouseUp(int key);

		virtual void onMouseMove();
		virtual void onMouseEnter();
		virtual void onMouseLeave();

	public:

		virtual bool over(double x, double y);

};