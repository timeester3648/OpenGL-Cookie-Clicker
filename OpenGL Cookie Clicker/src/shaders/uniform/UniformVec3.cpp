#include "../../../header/shaders/uniform/UniformVec3.h"

#include <GLFW\glfw3.h>

UniformVec3::UniformVec3(String name) : Uniform(name) {

}

UniformVec3::UniformVec3(String name, int location) : Uniform(name) {

	this->storeUniformLocation(location);

}

void UniformVec3::loadVec3(glm::vec3 v) {

	loadVec3(v.x, v.y, v.z);

}

void UniformVec3::loadVec3(float x, float y, float z) {

	if (!used || x != curX || y != curY || z != curZ) {

		this->curX = x;
		this->curY = y;
		this->curZ = z;
		this->used = true;

		glUniform3f(getLocation(), x, y, z);

	}

}