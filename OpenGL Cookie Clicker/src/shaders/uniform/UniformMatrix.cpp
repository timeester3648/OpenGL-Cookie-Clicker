#include "../../../header/shaders/uniform/UniformMatrix.h"

#include <GLFW\glfw3.h>

UniformMatrix::UniformMatrix(String name) : Uniform(name) {

}

UniformMatrix::UniformMatrix(String name, int location) : Uniform(name) {

	this->storeUniformLocation(location);

}

void UniformMatrix::loadMatrix(glm::mat4 mat) {

	glUniformMatrix4fv(getLocation(), 1, false, &mat[0][0]);

}