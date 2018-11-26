#pragma once

#include "../../util/TexturedModelCompare.h"
#include "../../shaders/StaticShader.h"
#include "../../interactable/ImageButton.h"

#include <glm\glm.hpp>
#include <map>
#include <vector>

typedef glm::mat4 Mat4;

class ButtonRenderer {

	public:

		StaticShader& shader;
		std::map<TexturedModel*, std::vector<ImageButton*>, TexturedModelCompare> buttons;

	public:

		ButtonRenderer(StaticShader& shader);

	public:

		void addImageButton(ImageButton* renderable);
		void prepareTexturedModel(const TexturedModel* model);
		void prepareInstance(const ImageButton* button);
		void unbindTexturedModel();

		void render();

};