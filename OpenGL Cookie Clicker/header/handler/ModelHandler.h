#pragma once

#include "../objects/TexturedModel.h"

#include <unordered_map>
#include <vector>
#include <string>

class ModelHandler {

	public:

		static std::unordered_map<int, TexturedModel*> textured_models;
		static std::vector<RawModel> raw_models;
		static std::vector<ModelTexture*> model_textures;

	private:

		static void addModel(std::string name, RawModel* raw_model, int cols = 1, int rows = 1);

	public:

		static void init();
		static void cleanUp();

		static TexturedModel* getModelById(int id);

};