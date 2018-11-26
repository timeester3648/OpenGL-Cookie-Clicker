#pragma once

#include <GL\glew.h>
#include <string>

typedef std::string String;

class ModelTexture {

	private:

		GLuint id;
		GLfloat shineDamper = 1;
		GLfloat reflectivity = 0;
		bool hasTransparency = false;
		bool useFakeLighting = false;
		GLuint numberOfRows = 1, numberOfColumns = 1;

	public:

		ModelTexture(GLuint id);

	private:

		ModelTexture() = default;

	public:

		GLuint getID() const;
		GLuint getNumberOfRows() const;
		GLuint getNumberOfColumns() const;

		void setNumberOfRows(GLuint r);
		void setNumberOfColumns(GLuint r);

};