#pragma once

#include "../../shaders/StaticShader.h"
#include "ButtonRenderer.h"
#include "StaticImageRenderer.h"
#include "InfoPaneRenderer.h"
#include "TextRenderer.h"

#include <glm\glm.hpp>
#include <vector>
#include <string>

typedef glm::mat4 Mat4;

class Renderer {

	public:

		static constexpr float NEAR_PLANE = .1f, FAR_PLANE = 1000.0f, FOV = 100.0f;
		static Mat4 projectionMatrix;

		StaticShader shader;
		TextShader text_shader;
		ButtonRenderer button_renderer;
		StaticImageRenderer static_image_renderer;
		InfoPaneRenderer info_pane_renderer;
		TextRenderer text_renderer;

	public:

		Renderer();

	public:

		void render();

};