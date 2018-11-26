#pragma once

#include "Uniform.h"

#include <glm/glm.hpp>

class UniformVec3 : public Uniform {

	private:

		float curX, curY, curZ;
		bool used = false;

	public:

		UniformVec3(String name);
		UniformVec3(String name, int location);

	private:

		UniformVec3() = default;

	public:

		void loadVec3(glm::vec3 v);
		void loadVec3(float x, float y, float z);

};