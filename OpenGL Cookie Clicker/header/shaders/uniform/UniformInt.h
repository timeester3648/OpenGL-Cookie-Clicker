#pragma once

#include "Uniform.h"

class UniformInt : public Uniform {

	private:

		int curValue;
		bool used = false;

	public:

		UniformInt(String name);
		UniformInt(String name, int location);

	private:

		UniformInt() = default;

	public:

		void loadInt(int i);

};