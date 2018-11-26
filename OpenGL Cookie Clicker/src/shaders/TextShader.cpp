#include "../../header/shaders/TextShader.h"
#include "../../header/util/MathHelper.h"

#include <iostream>

#define print(x) std::cout << x << std::endl

TextShader::TextShader() : ShaderProgram("src/shaders/textVertexShader.vs", "src/shaders/textFragmentShader.fs") {

	init();

}

void TextShader::bindAttributes() {

}

void TextShader::initUniforms() {

	mvp.storeUniformLocation(this->programID);

}

void TextShader::loadMVP(Mat4 mat) {

	mvp.loadMatrix(mat);

}