#pragma once

#include <GL\glew.h>
#include <fstream>
#include <string>
#include <iostream>
#include <glm\vec3.hpp>
#include <glm\mat4x4.hpp>

#include "uniform/include/Uniforms.h"

class ShaderProgram {

	protected:

		GLuint programID, vertexShaderID, fragmentShaderID;
		const char* vertexFile;
		const char* fragmentFile;

	protected:

		ShaderProgram(const char* vertexFile, const char* fragmentFile);
		ShaderProgram(const ShaderProgram& other) = delete;

	public:

		void start();
		void stop();
		void cleanUp();
		void init();

		virtual void bindAttributes() = 0;

	protected:

		virtual void initUniforms() = 0;

	protected:

		void bindAttribute(GLuint attribute, const char* var);

	private:

		GLuint loadShader(const char* file, GLuint type);


};