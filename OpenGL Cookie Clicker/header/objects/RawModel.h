#pragma once

#include <GL\glew.h>
#include <GLFW\glfw3.h>

class RawModel {

	friend class ModelHandler;

	private:

		GLuint vaoID;
		GLuint vertexCount;

	public:

		RawModel(GLuint vaoID, GLuint vertexCount);

	private:

		RawModel() = default;

	public:

		GLuint getVaoID() const;
		GLuint getVertexCount() const;

};