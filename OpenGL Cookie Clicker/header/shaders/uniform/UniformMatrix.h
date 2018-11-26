#pragma once

#include "Uniform.h"

#include <glm/glm.hpp>

class UniformMatrix : public Uniform {

	private:

		glm::mat4 curValue;

	public:

		UniformMatrix(String name);
		UniformMatrix(String name, int location);

	private:

		UniformMatrix() = default;

	public:

		void loadMatrix(glm::mat4 mat);

};