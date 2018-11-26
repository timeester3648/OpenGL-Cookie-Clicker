#pragma once

#include <GLFW\glfw3.h>

class DisplayManager {

	public:

		static GLFWwindow* window;
		static GLFWimage images[3];
		static int width, height;

	private:

		static void error_callback(int error, const char* description);
		static void window_size_callback(GLFWwindow* window, int width, int height);

	public:

		static void createDisplay();
		static void updateDisplay();
		static void closeDisplay();

};