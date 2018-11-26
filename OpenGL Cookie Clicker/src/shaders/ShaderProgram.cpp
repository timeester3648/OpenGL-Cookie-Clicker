#include "../../header/shaders/ShaderProgram.h"
#include "../../header/util/BuildType.h"

#include <glm\glm.hpp>
#include <iostream>

#define print(x) std::cout << x << std::endl

#ifdef BUILD_EXE		
	#pragma comment(linker, "/subsystem:windows /entry:mainCRTStartup")
#endif

ShaderProgram::ShaderProgram(const char* vertexFile, const char* fragmentFile) : vertexFile(vertexFile), fragmentFile(fragmentFile) {

}

GLuint ShaderProgram::loadShader(const char* file, GLuint type) {

	std::string f = file;

#ifdef BUILD_EXE
		
	f.erase(0, 4);

#endif

	std::ifstream in(f);
	std::string lines, line;

	while (getline(in, line)) {

		lines += line + '\n';

	}

	lines = lines.substr(0, lines.length() - 1);

	in.close();

	GLuint shaderID = glCreateShader(type);

	const char* adapter[1] = { lines.c_str() };

	glShaderSource(shaderID, 1, adapter, 0);
	glCompileShader(shaderID);

	return shaderID;

}

void ShaderProgram::bindAttribute(GLuint attribute, const char* var) {

	glBindAttribLocation(this->programID, attribute, var);

}

void ShaderProgram::init() {

	this->vertexShaderID = loadShader(this->vertexFile, GL_VERTEX_SHADER);
	this->fragmentShaderID = loadShader(this->fragmentFile, GL_FRAGMENT_SHADER);
	this->programID = glCreateProgram();

	glAttachShader(this->programID, this->vertexShaderID);
	glAttachShader(this->programID, this->fragmentShaderID);

	bindAttributes();

	glLinkProgram(this->programID);
	glValidateProgram(this->programID);

	initUniforms();

}

void ShaderProgram::start() {

	glUseProgram(programID);

}

void ShaderProgram::stop() {

	glUseProgram(0);

}

void ShaderProgram::cleanUp() {

	stop();

	glDetachShader(programID, vertexShaderID);
	glDetachShader(programID, fragmentShaderID);
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
	glDeleteProgram(programID);

}
