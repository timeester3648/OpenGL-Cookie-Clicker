#include "../../../header/shaders/uniform/UniformVec4.h"

#include <GLFW\glfw3.h>

UniformVec4::UniformVec4(String name) : Uniform(name) {

}

UniformVec4::UniformVec4(String name, int location) : Uniform(name) {

	this->storeUniformLocation(location);

}

void UniformVec4::loadVec4(glm::vec4 v) {

	loadVec4(v.x, v.y, v.z, v.w);

}

void UniformVec4::loadVec4(float x, float y, float z, float w) {

	if (!used || x != curX || y != curY || z != curZ || w != curW) {

		this->used = true;

		glUniform4f(getLocation(), x, y, z, w);

	}

}