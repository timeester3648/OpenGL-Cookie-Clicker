#pragma once

#include <string>

typedef std::string String;

class ShaderProgram;

class Uniform {

	friend class ShaderProgram;

	private:

		static constexpr int NOT_FOUND = -1;
		String name;
		int location;

	protected:

		Uniform(String name);
		Uniform(String name, int location);

	private:

		Uniform() = default;

	public:

		void storeUniformLocation(int programID);
		int getLocation();

};