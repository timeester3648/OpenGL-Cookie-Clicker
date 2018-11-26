#include "../../../header/shaders/uniform/Uniform.h"
#include "../../../header/shaders/ShaderProgram.h"

#include <iostream>
#include <GLFW\glfw3.h>

#define print(x) std::cout << x << std::endl
#define error(x) std::cerr << x << std::endl

Uniform::Uniform(String name) : name(name) {

}

Uniform::Uniform(String name, int location) : Uniform(name) {

	this->storeUniformLocation(location);

}

void Uniform::storeUniformLocation(int programID) {

	this->location = glGetUniformLocation(programID, this->name.c_str());

	if (this->location == NOT_FOUND) {

		error(std::string("No uniform variable called \"") + this->name + "\" found for shader program: " + std::to_string(programID));

	}

}

int Uniform::getLocation() {

	return this->location;

}