#include "../../../header/shaders/uniform/UniformFloat.h"

#include <GLFW\glfw3.h>

UniformFloat::UniformFloat(String name) : Uniform(name) {

}

UniformFloat::UniformFloat(String name, int location) : Uniform(name) {

	this->storeUniformLocation(location);

}

void UniformFloat::loadFloat(float value) {

	if (!used || curValue != value) {

		glUniform1f(getLocation(), value);

		this->used = true;
		this->curValue = value;

	}

}