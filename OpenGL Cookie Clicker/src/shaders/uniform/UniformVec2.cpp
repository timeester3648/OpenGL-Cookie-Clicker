#include "../../../header/shaders/uniform/UniformVec2.h"

#include <GLFW\glfw3.h>

UniformVec2::UniformVec2(String name) : Uniform(name) {

}

UniformVec2::UniformVec2(String name, int location) : Uniform(name) {

	this->storeUniformLocation(location);

}

void UniformVec2::loadVec2(glm::vec2 v) {

	loadVec2(v.x, v.y);

}

void UniformVec2::loadVec2(float x, float y) {

	if (!used || x != curX || y != curY) {

		this->curX = x;
		this->curY = y;
		this->used = true;

		glUniform2f(getLocation(), x, y);

	}

}