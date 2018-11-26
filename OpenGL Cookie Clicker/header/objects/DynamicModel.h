#pragma once

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <vector>

class DynamicModel {

	friend class ModelHandler;

	private:

		GLuint vaoID;
		GLuint vertexCount;

	public:

		std::vector<GLuint> vbos;

	public:

		DynamicModel(GLuint vaoID, GLuint vertexCount);

	private:

		DynamicModel() = default;

	public:

		GLuint getVaoID() const;
		GLuint getVertexCount() const;

};