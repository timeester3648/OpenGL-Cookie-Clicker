#include "../../header/display/DisplayManager.h"
#include "../../header/handler/MouseHandler.h"

#include <EOUL.hpp>
#include <iostream>

#define null NULL

GLFWwindow* DisplayManager::window;
GLFWimage DisplayManager::images[3];

int DisplayManager::width = 1080, DisplayManager::height = (width / 16) * 9;

void DisplayManager::error_callback(int error, const char* description) {

	puts(description);

}

void DisplayManager::window_size_callback(GLFWwindow* window, int width, int height) {

	DisplayManager::width = width;
	DisplayManager::height = height;

}

void DisplayManager::createDisplay() {

	glfwSetErrorCallback(error_callback);

	if (!glfwInit()) {

		glfwTerminate();

	}

	using namespace EOUL::IO;

	Image icon = Image("res/icon.png");

	images[0].width = icon.getWidth();
	images[0].height = icon.getHeight();
	images[0].pixels = const_cast<unsigned char*>(icon.getPixels());

	Image icon_small = Image("res/icon_small.png");

	images[1].width = icon_small.getWidth();
	images[1].height = icon_small.getHeight();
	images[1].pixels = const_cast<unsigned char*>(icon_small.getPixels());

	Image icon_tiny = Image("res/icon_tiny.png");

	images[2].width = icon_tiny.getWidth();
	images[2].height = icon_tiny.getHeight();
	images[2].pixels = const_cast<unsigned char*>(icon_tiny.getPixels());

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	window = glfwCreateWindow(width, height, "Cookie Clicker", null, null);

	glfwSetWindowSizeCallback(window, window_size_callback);
	glfwSetWindowIcon(window, 3, images);
	glfwMakeContextCurrent(window);

	glfwSetMouseButtonCallback(DisplayManager::window, MouseHandler::mouse_input_callback);
	glfwSetCursorPosCallback(DisplayManager::window, MouseHandler::mouse_move_callback);
	glfwSetScrollCallback(DisplayManager::window, MouseHandler::scroll_callback);

	if (glewInit() != GLEW_OK) {

		glfwTerminate();

	}

	// V-Sync
	glfwSwapInterval(1);

	std::cout << glfwGetVersionString() << std::endl;

}

void DisplayManager::updateDisplay() {

	glfwSwapBuffers(window);
	glfwPollEvents();

}

void DisplayManager::closeDisplay() {

	glfwTerminate();

}