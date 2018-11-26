#include "../../header/util/MathHelper.h"
#include "../../header/display/DisplayManager.h"
#include "../../header/display/render/Renderer.h"

#include <glm\gtx\transform.hpp>
#include <EOUL\Maths.h>
#include <iostream>

using namespace EOUL::Math;

Mat4 MathHelper::createTransformationMatrix(Vec2 translation, float rotation, Vec2 scale) {

	Mat4 transMatrix = glm::translate(Vec3(translation, 0.0f));
	Mat4 rotMatrix = glm::rotate((float) radians(rotation), Vec3(0, 0, 1));
	Mat4 scaleMatrix = glm::scale(Vec3(scale, 1.0f));

	return transMatrix * rotMatrix * scaleMatrix;

}

Mat4 MathHelper::createTransformationMatrix(Vec2 translation, Vec2 scale) {

	Mat4 transMatrix = glm::translate(Vec3(translation, 0.0f));
	Mat4 scaleMatrix = glm::scale(Vec3(scale, 1.0f));

	return transMatrix * scaleMatrix;

}

Mat4 MathHelper::createProjectionMatrix() {

	Mat4 projectionMatrix;

	float aspectRatio = (float) DisplayManager::width / (float) DisplayManager::height;
	float y_scale = (float) ((1.0f / tan(radians(Renderer::FOV / 2.0f))) * aspectRatio);
	float x_scale = y_scale / aspectRatio;
	float frustum_length = Renderer::FAR_PLANE - Renderer::NEAR_PLANE;

	projectionMatrix = Mat4();
	projectionMatrix[0][0] = x_scale;
	projectionMatrix[1][1] = y_scale;
	projectionMatrix[2][2] = -((Renderer::FAR_PLANE + Renderer::NEAR_PLANE) / frustum_length);
	projectionMatrix[2][3] = -1;
	projectionMatrix[3][2] = -((2 * Renderer::NEAR_PLANE * Renderer::FAR_PLANE) / frustum_length);
	projectionMatrix[3][3] = 0;

	return projectionMatrix;

}

Vec2 MathHelper::glfwToWindowCoord(Vec2 coords, Vec2 scale) {

	Mat4 proj = Renderer::projectionMatrix;
	Mat4 trans = createTransformationMatrix(coords, scale);

	Vec4 position = proj * trans * Vec4(0, 0, -1.0, 1.0);

	return { (float) map(position.x, -1.0f, 1.0f, 0, DisplayManager::width), (float) map(position.y, 1.0f, -1.0f, 0, DisplayManager::height) };

}

Vec2 MathHelper::glfwToTextCoord(Vec2 coords, Vec2 scale) {

	Mat4 proj = Renderer::projectionMatrix;
	Mat4 trans = createTransformationMatrix(coords, scale);

	Vec4 position = proj * trans * Vec4(0, 0, -1.0, 1.0);

	return { (float) map(position.x, -1.0f, 1.0f, 0, DisplayManager::width), (float) map(position.y, 1.0f, -1.0f, DisplayManager::height, 0) };

}

Vec2 MathHelper::windowToGLFWCoord(Vec2 coords) {

	return { (float) map(coords.x, 0, DisplayManager::width, -1, 1), (float) map(coords.y, 0, DisplayManager::height, 1, -1) };

}

Vec2 MathHelper::windowToGLFWSize(Vec2 coords) {

	return windowToGLFWCoord(coords) - windowToGLFWCoord({ 0, 0 });

}

Vec2 MathHelper::textToGLFWCoord(Vec2 coords) {

	return { (float) map(coords.x, 0, DisplayManager::width, -1, 1), (float) map(coords.y, 0, DisplayManager::height, -1, 1) };

}