#pragma once

#include <GL\glew.h>

#include "RawModel.h"
#include "../objects/ModelTexture.h"

class ModelHandler;

class TexturedModel {

	friend class ModelHandler;

	private:

		RawModel* rawModel;
		ModelTexture* texture;

	public:

		TexturedModel(RawModel* model, ModelTexture* texture);
		TexturedModel(const TexturedModel& copy);

	private:

		TexturedModel() = default;

	public:

		RawModel& getRawModel() const;
		ModelTexture& getTexture() const;



};