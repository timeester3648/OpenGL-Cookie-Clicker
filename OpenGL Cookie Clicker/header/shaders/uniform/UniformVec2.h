#pragma once

#include "Uniform.h"

#include <glm/glm.hpp>

class UniformVec2 : public Uniform {

	private:

		float curX, curY;
		bool used = false;

	public:

		UniformVec2(String name);
		UniformVec2(String name, int location);

	private:

		UniformVec2() = default;

	public:

		void loadVec2(glm::vec2 v);
		void loadVec2(float x, float y);

};