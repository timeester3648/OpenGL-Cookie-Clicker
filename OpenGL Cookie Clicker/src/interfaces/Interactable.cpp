#include "../../header/interfaces/Interactable.h"
#include "../../header/util/MathHelper.h"

#include <EOUL\Maths.h>
#include <iostream>
#include <glm\glm.hpp>
#include <isect2d\isect2d.h>

typedef isect2d::OBB<glm::vec2> OBB;

using namespace EOUL::Math;

Interactable::Interactable(Vec2 position, Vec2 scale) : position(position), scale(scale) {

}

void Interactable::onKeyDown(int key) {

}

void Interactable::onKeyUp(int key) {

}

void Interactable::onMouseDown(int key) {

}

void Interactable::onMouseUp(int key) {

}

void Interactable::onMouseMove() {

}

void Interactable::onMouseEnter() {

}

void Interactable::onMouseLeave() {

}

bool Interactable::over(double x, double y) {

	Vec2 tmp_scl = this->scale;

	tmp_scl.y *= -1;

	Vec2 pos = MathHelper::glfwToWindowCoord(this->position, this->scale);
	Vec2 top_left = MathHelper::glfwToWindowCoord(this->position - tmp_scl, this->scale);
	Vec2 bottom_right = MathHelper::glfwToWindowCoord(this->position + tmp_scl, this->scale);

	return (x >= top_left.x && x <= bottom_right.x) && (y >= top_left.y && y <= bottom_right.y);

}