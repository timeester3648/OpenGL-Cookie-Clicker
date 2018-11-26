#pragma once

#include "ShaderProgram.h"

#include <GL\glew.h>
#include <glm\glm.hpp>

typedef glm::vec4 Vec4;
typedef glm::vec3 Vec3;
typedef glm::vec2 Vec2;
typedef glm::mat4 Mat4;

class TextShader : public ShaderProgram {

	public:

		UniformMatrix mvp = UniformMatrix("mvp");

	public:

		TextShader();

	public:

		virtual void bindAttributes() override;
		virtual void initUniforms() override;

		void loadMVP(Mat4 mat);

};