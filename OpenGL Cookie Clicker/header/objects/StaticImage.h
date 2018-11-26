#pragma once

#include "TexturedModel.h"

#include <glm\glm.hpp>

typedef glm::vec2 Vec2;
typedef glm::vec3 Vec3;
typedef glm::vec4 Vec4;

class StaticImage {

	public:

		Vec2 position, scale, offset;
		float rotation;
		TexturedModel* textured_model;
		Vec4 mixColor = { 1.0f, 1.0f, 1.0f, 1.0f };
		bool doMixColor = false;
		float mixIntensity = .5f;
		bool blacked_out = false;

	public:

		StaticImage(Vec2 position, Vec2 scale, TexturedModel* textured_model, float rotation = 0.0f, Vec2 offset = { 0, 0 });

		virtual ~StaticImage() = default;

	public:

		Vec2 getTextureOffset() const;

};