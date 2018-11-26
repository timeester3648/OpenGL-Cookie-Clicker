#pragma once

#include "Uniform.h"

class UniformSampler : public Uniform {

	private:

		int curValue;
		bool used = false;

	public:

		UniformSampler(String name);
		UniformSampler(String name, int location);

	private:

		UniformSampler() = default;

	public:

		void loadTexUnit(int t);

};