#include "../../header/objects/DynamicModel.h"

#include <iostream>

DynamicModel::DynamicModel(GLuint vaoID, GLuint vertexCount) : vaoID(vaoID), vertexCount(vertexCount) {

}

GLuint DynamicModel::getVaoID() const {

	return this->vaoID;

}

GLuint DynamicModel::getVertexCount() const {

	return this->vertexCount;

}