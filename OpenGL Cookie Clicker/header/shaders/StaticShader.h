#pragma once

#include "ShaderProgram.h"

#include <GL\glew.h>
#include <glm\glm.hpp>

typedef glm::vec4 Vec4;
typedef glm::vec3 Vec3;
typedef glm::vec2 Vec2;

class StaticShader : public ShaderProgram {

	public:

		UniformMatrix transformationMatrix = UniformMatrix("transformationMatrix"), projectionMatrix = UniformMatrix("projectionMatrix");
		UniformVec2 offset = UniformVec2("offset");
		UniformVec4 colorMix = UniformVec4("colorMix");
		UniformInt numberRows = UniformInt("numberRows"), numberColumns = UniformInt("numberColumns");
		UniformBool doMixColor = UniformBool("doMixColor"), iconLocked = UniformBool("iconLocked");
		UniformFloat mixColorIntensity = UniformFloat("mixColorIntensity");

	public:

		StaticShader();

	public:

		virtual void bindAttributes() override;
		virtual void initUniforms() override;

		void loadTransformationMatrix(glm::mat4 mat);
		void loadProjectionMatrix(glm::mat4 mat);
		void loadOffset(Vec2 offset);
		void loadNumberOfRows(int n);
		void loadNumberOfColumns(int n);
		void loadMixColor(bool mix, Vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f }, float intensity = .5f);
		void loadIconLocked(bool locked);

};