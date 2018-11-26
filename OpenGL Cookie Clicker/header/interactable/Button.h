#pragma once

#include "../interfaces/Interactable.h"
#include "../sound/Sound.h"

#include <GLFW\glfw3.h>

class Button : public Interactable {

	protected:

		bool mouse_over = false;
		bool mouse_down = false;

		Sound* sound = nullptr;

	protected:	

		static GLFWcursor *hand, *arrow;

	public:

		Button(Vec2 position, Vec2 scale);

		virtual ~Button() = default;

	public:

		virtual void onMouseDown(int key) override;
		virtual void onMouseUp(int key) override;

		virtual void onMouseEnter() override;
		virtual void onMouseLeave() override;
		virtual void update() override;

	public:

		virtual void activate() = 0;

};