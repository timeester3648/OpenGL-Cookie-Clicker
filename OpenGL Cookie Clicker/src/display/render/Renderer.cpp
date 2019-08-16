#include "../../../header/display/render/Renderer.h"
#include "../../../header/display/DisplayManager.h"
#include "../../../header/util/MathHelper.h"

#include <EOUL\Maths.hpp>
#include <glm\gtx\transform.hpp>

using namespace EOUL::Math;

Mat4 Renderer::projectionMatrix;

Renderer::Renderer() : button_renderer(shader), static_image_renderer(shader), text_renderer(TextRenderer(text_shader)), info_pane_renderer(InfoPaneRenderer(shader)) {

	this->projectionMatrix = MathHelper::createProjectionMatrix();

	this->shader.start();
	this->shader.loadProjectionMatrix(this->projectionMatrix);
	this->shader.stop();

}

void Renderer::render() {

	this->static_image_renderer.render();
	this->button_renderer.render();
	this->static_image_renderer.render_overlays();
	this->info_pane_renderer.render();
	this->text_renderer.render();

}