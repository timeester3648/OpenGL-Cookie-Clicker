#pragma once

#ifndef EOUL_USE_GLFW_INPUT
	#include <Windows.h>
#else
	#include <GL\glew.h>
	#include <GLFW\glfw3.h>
#endif

namespace EOUL {

	namespace Util {

		#ifndef EOUL_USE_GLFW_INPUT
			
			/* returns if the given key is down */
			inline bool isKeyDown(int key) {

				return GetAsyncKeyState(key);

			}

			/* returns if the given key is up */
			inline bool isKeyUp(int key) {

				return !isKeyDown(key);

			}

		#else

			/* returns if the given key is down */
			inline bool isKeyDown(GLFWwindow* window, int key) {

				return (glfwGetKey(window, key) == GL_TRUE);

			}

			/* returns if the given key is up */
			inline bool isKeyUp(GLFWwindow* window, int key) {

				return !isKeyDown(window, key);

			}

		#endif

		/* returns how much physical ram is free */
		unsigned long long ramFree();
		/*  returns how much physical ram is used */
		unsigned long long ramUsed();
		/* returns how much physical ram is used by current process */
		unsigned long long ramUsedByCurrent();

	}

}