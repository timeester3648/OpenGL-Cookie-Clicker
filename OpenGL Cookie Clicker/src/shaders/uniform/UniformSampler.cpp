#include "../../../header/shaders/uniform/UniformSampler.h"

#include <GLFW\glfw3.h>

UniformSampler::UniformSampler(String name) : Uniform(name) {

}

UniformSampler::UniformSampler(String name, int location) : Uniform(name) {

	this->storeUniformLocation(location);

}

void UniformSampler::loadTexUnit(int t) {

	if (!used || curValue != t) {

		glUniform1i(getLocation(), t);

		this->used = true;
		this->curValue = t;

	}

}