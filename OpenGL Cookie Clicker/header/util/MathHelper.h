#pragma once

#include <glm\glm.hpp>
#include <vector>

typedef glm::mat4 Mat4;
typedef glm::vec3 Vec3;
typedef glm::vec2 Vec2;

class MathHelper {

	public:

		static Mat4 createTransformationMatrix(Vec2 translation, float rotation, Vec2 scale);
		static Mat4 createTransformationMatrix(Vec2 translation, Vec2 scale);
		static Mat4 createProjectionMatrix();
		static Vec2 glfwToWindowCoord(Vec2 coords, Vec2 scale);
		static Vec2 glfwToTextCoord(Vec2 coords, Vec2 scale);
		static Vec2 windowToGLFWCoord(Vec2 coords);
		static Vec2 textToGLFWCoord(Vec2 coords);
		static Vec2 windowToGLFWSize(Vec2 coords);			 

};