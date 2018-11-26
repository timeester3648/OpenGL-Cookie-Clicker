#include "../../header/shaders/StaticShader.h"
#include "../../header/util/MathHelper.h"

#include <iostream>

#define print(x) std::cout << x << std::endl

StaticShader::StaticShader() : ShaderProgram("src/shaders/vertexShader.vs", "src/shaders/fragmentShader.fs") {

	init();

}

void StaticShader::bindAttributes() {

	bindAttribute(0, "position");
	bindAttribute(1, "textureCoords");

}

void StaticShader::initUniforms() {

	transformationMatrix.storeUniformLocation(this->programID);
	projectionMatrix.storeUniformLocation(this->programID);
	numberRows.storeUniformLocation(this->programID);
	numberColumns.storeUniformLocation(this->programID);
	offset.storeUniformLocation(this->programID);
	colorMix.storeUniformLocation(this->programID);
	doMixColor.storeUniformLocation(this->programID);
	mixColorIntensity.storeUniformLocation(this->programID);
	iconLocked.storeUniformLocation(this->programID);

}

void StaticShader::loadTransformationMatrix(glm::mat4 mat) {

	transformationMatrix.loadMatrix(mat);

}

void StaticShader::loadProjectionMatrix(glm::mat4 mat) {

	projectionMatrix.loadMatrix(mat);

}

void StaticShader::loadOffset(Vec2 v) {

	offset.loadVec2(v);

}

void StaticShader::loadNumberOfRows(int n) {

	numberRows.loadInt(n);

}

void StaticShader::loadNumberOfColumns(int n) {

	numberColumns.loadInt(n);

}

void StaticShader::loadMixColor(bool mix, Vec4 color, float intensity) {

	doMixColor.loadBool(mix);
	colorMix.loadVec4(color);
	mixColorIntensity.loadFloat(intensity);

}

void StaticShader::loadIconLocked(bool locked) {

	iconLocked.loadBool(locked);

}