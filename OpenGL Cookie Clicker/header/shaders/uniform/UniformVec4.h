#pragma once

#include "Uniform.h"

#include <glm/glm.hpp>

class UniformVec4 : public Uniform {

	private:

		float curX, curY, curZ, curW;
		bool used = false;

	public:

		UniformVec4(String name);
		UniformVec4(String name, int location);

	private:

		UniformVec4() = default;

	public:

		void loadVec4(glm::vec4 v);
		void loadVec4(float x, float y, float z, float w);

};