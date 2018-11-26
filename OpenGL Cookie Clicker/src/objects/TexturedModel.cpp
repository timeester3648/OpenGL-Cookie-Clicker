#include "../../header/objects/TexturedModel.h"

#include <iostream>

#define print(x) std::cout << x << std::endl

TexturedModel::TexturedModel(RawModel* model, ModelTexture* texture) : rawModel(model), texture(texture) {

}

TexturedModel::TexturedModel(const TexturedModel& copy) : rawModel(copy.rawModel), texture(copy.texture) {

}

RawModel& TexturedModel::getRawModel() const {

	return *this->rawModel;

}

ModelTexture& TexturedModel::getTexture() const {

	return *this->texture;

}
