#include "../../../header/shaders/uniform/UniformInt.h"

#include <GLFW\glfw3.h>

UniformInt::UniformInt(String name) : Uniform(name) {

}

UniformInt::UniformInt(String name, int location) : Uniform(name) {

	this->storeUniformLocation(location);

}

void UniformInt::loadInt(int value) {

	if (!used || curValue != value) {

		glUniform1i(getLocation(), value);

		this->used = true;
		this->curValue = value;

	}

}