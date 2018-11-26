#include "../../../header/shaders/uniform/UniformBool.h"

#include <GLFW\glfw3.h>

UniformBool::UniformBool(String name) : Uniform(name) {

}

UniformBool::UniformBool(String name, int location) : Uniform(name) {

	this->storeUniformLocation(location);

}

void UniformBool::loadBool(bool b) {

	if (!used || current != b) {

		glUniform1f(getLocation(), b ? 1.0f : 0.0f);

		this->used = true;
		this->current = b;

	}

}