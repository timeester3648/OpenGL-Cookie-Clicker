#include "../../header/shaders/FontShader.h"
#include "../../header/util/MathHelper.h"

#include <iostream>

#define print(x) std::cout << x << std::endl

FontShader::FontShader() : ShaderProgram("src/shaders/fontVertexShader.vs", "src/shaders/fontFragmentShader.fs") {

	init();

}

void FontShader::bindAttributes() {

	bindAttribute(0, "position");
	bindAttribute(1, "textureCoords");

}

void FontShader::initUniforms() {

	color.storeUniformLocation(this->programID);
	translation.storeUniformLocation(this->programID);

}

void FontShader::loadColor(Vec3 color) {

	this->color.loadVec3(color);

}

void FontShader::loadTranslation(Vec2 translation) {

	this->translation.loadVec2(translation);

}