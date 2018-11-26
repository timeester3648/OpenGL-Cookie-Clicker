#pragma once

#include "../../util/TexturedModelCompare.h"
#include "../../shaders/StaticShader.h"
#include "../../objects/StaticImage.h"

#include <glm\glm.hpp>
#include <map>
#include <vector>

typedef glm::mat4 Mat4;

class StaticImageRenderer {

	public:

		StaticShader& shader;
		std::map<TexturedModel*, std::vector<StaticImage*>, TexturedModelCompare> static_images;
		std::map<TexturedModel*, std::vector<StaticImage*>, TexturedModelCompare> overlays;

	public:

		StaticImageRenderer(StaticShader& shader);

	public:

		void addStaticImage(StaticImage* image);
		void addOverlay(StaticImage* image);
		void prepareTexturedModel(const TexturedModel* model);
		void prepareInstance(const StaticImage* image);
		void unbindTexturedModel();

		void render();
		void render_overlays();

};