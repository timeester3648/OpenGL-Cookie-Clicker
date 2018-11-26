#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

typedef glm::vec2 Vec2;

class MouseHandler {

	public:

		static bool leftMouseDown, rightMouseDown;
		static double mouseX, mouseY;

	public:

		static void onMouseMove();

		static void mouse_move_callback(GLFWwindow* window, double x, double y);
		static void mouse_input_callback(GLFWwindow* window, int button, int action, int mods);
		static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

};