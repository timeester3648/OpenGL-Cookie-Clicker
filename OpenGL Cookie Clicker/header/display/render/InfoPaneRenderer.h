#pragma once

#include "../../shaders/StaticShader.h"
#include "../../ui/UpgradeInfoPane.h"
#include "../../ui/BuildingInfoPane.h"

#include <glm\glm.hpp>
#include <vector>

typedef glm::mat4 Mat4;

class InfoPaneRenderer {

	public:

		StaticShader& shader;
		std::vector<UpgradeInfoPane*> upgrade_info_panes;
		std::vector<BuildingInfoPane*> building_info_panes;

	public:

		InfoPaneRenderer(StaticShader& shader);

	public:

		void addUpgradeInfoPane(UpgradeInfoPane* info_pane);
		void addBuildingInfoPane(BuildingInfoPane* info_pane);
		void prepareTexturedModel(const TexturedModel* model);
		void prepareInstance(const StaticImage* image);
		void unbindTexturedModel();

		void render();

};