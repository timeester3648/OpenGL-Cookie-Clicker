#include "../../header/objects/ModelTexture.h"

#include <iostream>

ModelTexture::ModelTexture(GLuint id) : id(id) {

}

GLuint ModelTexture::getID() const {

	return this->id;

}

GLuint ModelTexture::getNumberOfRows() const {

	return this->numberOfRows;

}

void ModelTexture::setNumberOfRows(GLuint r) {

	this->numberOfRows = r;

}

GLuint ModelTexture::getNumberOfColumns() const {

	return this->numberOfColumns;

}

void ModelTexture::setNumberOfColumns(GLuint r) {

	this->numberOfColumns = r;

}