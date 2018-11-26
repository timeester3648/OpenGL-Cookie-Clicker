#pragma once

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <vector>

#include "../objects/RawModel.h"
#include "../objects/DynamicModel.h"

class Loader {

	friend class Font;

	private:

		static std::vector<const GLuint*> vaos, vbos, textures;

	public:

		static RawModel loadToVAO(std::vector<GLfloat> positions, std::vector<GLfloat> textureCoords, std::vector<GLuint> indices);
		static DynamicModel loadToDynamicModel(std::vector<GLfloat> positions, std::vector<GLfloat> textureCoords, std::vector<GLuint> indices);
		static GLuint loadToVAO(std::vector<GLfloat> positions, std::vector<GLfloat> textureCoords);
		static RawModel loadToVAO(std::vector<GLfloat> positions);
		static void bindIndicesBuffer(std::vector<GLuint> indices, bool dynamic = false);
		static GLuint loadTexture(const char* path);
		static GLuint loadStaticFont(const char* path);
		static void cleanUp();
		static GLuint createVAO();
		static GLuint storeDataInAttributeList(int attributeNumber, int coordSize, std::vector<GLfloat> data, bool dynamic = false);
		static void unbindVAO();

};
