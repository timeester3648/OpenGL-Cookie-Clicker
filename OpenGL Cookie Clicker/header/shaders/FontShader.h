#pragma once

#include "ShaderProgram.h"

#include <GL\glew.h>
#include <glm\glm.hpp>

typedef glm::vec4 Vec4;
typedef glm::vec3 Vec3;
typedef glm::vec2 Vec2;

class FontShader : public ShaderProgram {

	public:

		UniformVec3 color = UniformVec3("color");
		UniformVec2 translation = UniformVec2("translation");

	public:

		FontShader();

	public:

		virtual void bindAttributes() override;
		virtual void initUniforms() override;

		void loadColor(Vec3 color);
		void loadTranslation(Vec2 translation);

};