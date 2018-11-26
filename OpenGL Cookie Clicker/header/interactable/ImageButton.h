#pragma once

#include "Button.h"
#include "../objects/TexturedModel.h"

#include <glm\glm.hpp>

typedef glm::vec2 Vec2;
typedef glm::vec4 Vec4;

class ImageButton : public Button {

	public:

		TexturedModel* textured_model;
		Vec2 offset = { 0, 0 };
		Vec4 mixColor = { 1.0f, 1.0f, 1.0f, 1.0f };
		bool doMixColor = false;
		float mixIntensity = .5f;

	public:

		ImageButton(Vec2 position, Vec2 scale, TexturedModel* textured_model);

		virtual ~ImageButton() = default;

	public:

		Vec2 getTextureOffset() const;

		virtual void activate() = 0;

};