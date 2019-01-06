#include "../../header/handler/ModelHandler.h"
#include "../../header/loading/Loader.h"

#include <algorithm>

std::unordered_map<int, TexturedModel*> ModelHandler::textured_models = std::unordered_map<int, TexturedModel*>();
std::vector<RawModel> ModelHandler::raw_models = std::vector<RawModel>();
std::vector<ModelTexture*> ModelHandler::model_textures = std::vector<ModelTexture*>();

void ModelHandler::init() {

	std::vector<GLfloat> positions = {

		-1.0f,  1.0f,
		-1.0f, -1.0f,
		 1.0f, -1.0f,
		 1.0f,  1.0f

	};

	std::vector<GLfloat> textureCoords = {

		0, 0,
		0, 1,
		1, 1,
		1, 0

	};

	std::vector<GLuint> indices = {

		0, 1, 3,
		3, 1, 2

	};

	raw_models.push_back(Loader::loadToVAO(positions, textureCoords, indices));

	addModel("perfectCookie", &raw_models[0]);
	addModel("bgBlue", &raw_models[0]);
	addModel("blackGradient", &raw_models[0]);
	addModel("black_alpha", &raw_models[0]);
	addModel("shine", &raw_models[0]);
	addModel("storeTile", &raw_models[0], 1, 4);
	addModel("shadedBordersSoft", &raw_models[0]);
	addModel("buildings", &raw_models[0], 4, 16);
	addModel("money", &raw_models[0]);
	addModel("panel", &raw_models[0]);
	addModel("shadedBorders", &raw_models[0]);
	addModel("icons", &raw_models[0], 30, 31);
	addModel("upgradeFrame", &raw_models[0], 3, 2);
	addModel("darkNoise", &raw_models[0]);
	addModel("panel_small", &raw_models[0]);

}

void ModelHandler::addModel(std::string name, RawModel* raw_model, int cols, int rows) {

	static int index = 0;

	ModelTexture* texture = new ModelTexture(Loader::loadTexture(name.c_str()));
	TexturedModel* textured_model = new TexturedModel(raw_model, texture);

	texture->setNumberOfColumns(cols);
	texture->setNumberOfRows(rows);

	model_textures.push_back(texture);

	textured_models.insert(std::unordered_map<int, TexturedModel*>::value_type(index, textured_model));

	index++;

}

void ModelHandler::cleanUp() {

	std::for_each(model_textures.begin(), model_textures.end(), [&](const ModelTexture* model) {
		
		delete model;
	
	});

	std::for_each(textured_models.begin(), textured_models.end(), [&](const std::pair<int, const TexturedModel*>& pair) {
		
		delete pair.second;
	
	});

	textured_models.clear();

	model_textures.clear();
	model_textures.shrink_to_fit();

}

TexturedModel* ModelHandler::getModelById(int id) {

	auto it = std::find_if(textured_models.begin(), textured_models.end(), [&](const std::pair<int, const TexturedModel*>& pair) {
		
		return pair.first == id;
	
	});

	return (it == textured_models.end() ? nullptr : it->second);

}