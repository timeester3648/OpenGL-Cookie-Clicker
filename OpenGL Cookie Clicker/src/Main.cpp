#include "../header/handler/InteractableHandler.h"
#include "../header/display/render/Renderer.h"
#include "../header/display/DisplayManager.h"
#include "../header/handler/UpgradeHandler.h"
#include "../header/handler/EffectHandler.h"
#include "../header/loading/UpgradeLoader.h"
#include "../header/objects/TexturedModel.h"
#include "../header/handler/CookieHandler.h"
#include "../header/handler/ModelHandler.h"
#include "../header/handler/AudioHandler.h"
#include "../header/handler/MouseHandler.h"
#include "../header/handler/FontHandler.h"
#include "../header/handler/ShopHandler.h"
#include "../header/game/GameSettings.h"
#include "../header/util/MathHelper.h"
#include "../header/game/PlayerData.h"
#include "../header/shop/ShopPrices.h"
#include "../header/util/BuildType.h"
#include "../header/util/Formatter.h"
#include "../header/loading/Loader.h"
#include "../header/game/GameSaver.h"
#include "../header/shop/ShopTile.h"
#include "../header/text/Font.h"
#include "../header/shop/Shop.h"
#include "../header/Main.h"

#define EOUL_USE_GLFW_INPUT
#define EOUL_USE_ALL
#include <EOUL.h>
#include <iostream>
#include <chrono>
#include <filesystem>
#include <thread>

#define clock std::chrono::high_resolution_clock
#define print(x) std::cout << x << std::endl

static float rotation_speed = .2f;

Renderer* renderer;
std::vector<std::thread*> threads;

CookieButton* button;
StaticImage *background, *background1, *background2, *text_background;
StaticImage *gradient, *gradient_top, *shop_gradient_top;
StaticImage *shine_rotate_left, *shine_rotate_right;
StaticImage *panel_0, *panel_1, *panel_2, *panel_3;
Label* shop_label;

void render_header_text();
void init();

int main() {

	UpgradeLoader::load();
	Formatter::init();
	ShopHandler::init();

	GameSaver::load_game();
	DisplayManager::createDisplay();

	renderer = new Renderer();

	CookieHandler::init();
	ModelHandler::init();
	AudioHandler::init();
	GameSettings::init();
	PlayerData::init();
	Shop::init();

	UpgradeHandler::update_upgrades();

	init();

	auto lastTime = clock::now();
	double ns = 1000000000.0 / (double) GameSettings::fps;
	double delta = 0;

	while (!glfwWindowShouldClose(DisplayManager::window)) {

		auto now = clock::now();

		delta += (now - lastTime).count() / ns;
		lastTime = now;

		while (delta >= 1) {

			InteractableHandler::update();
			EffectHandler::update();
			ShopHandler::update();
			CookieHandler::update();
			UpgradeHandler::update();

			shine_rotate_left->rotation -= rotation_speed;
			shine_rotate_right->rotation += rotation_speed;
		
			delta--;

		}		

		if (!glfwWindowShouldClose(DisplayManager::window)) {

			glClear(GL_COLOR_BUFFER_BIT);
			glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

#ifndef BUILD_EXE

			if (isKeyDown(DisplayManager::window, GLFW_KEY_ESCAPE)) {

				glfwSetWindowShouldClose(DisplayManager::window, GL_TRUE);

			}

#endif

			renderer->render();

			render_header_text();

			DisplayManager::updateDisplay();

		}

	}

	for (auto& thread : threads) {

		if (thread->joinable()) {

			thread->join();

		}

	}
	
	Loader::cleanUp();
	AudioHandler::cleanUp();
	ModelHandler::cleanUp();
	DisplayManager::closeDisplay();

}

void init() {

	button = new CookieButton({ -.725f, 0.0f }, { .2f, .2f });
	background = new StaticImage({ -.75f, 0 }, { .5f, 1.0f }, ModelHandler::getModelById(1));
	background1 = new StaticImage({ .75f, 0 }, { .5f, 1.0f }, ModelHandler::getModelById(1));
	background2 = new StaticImage({ 0, 0 }, { .5f, 1.0f }, ModelHandler::getModelById(1));
	gradient = new StaticImage({ -.75f, -.2f }, { .5f, 1.0f }, ModelHandler::getModelById(2));
	gradient_top = new StaticImage({ -.75f, .6f }, { .5f, 1.0f }, ModelHandler::getModelById(2), 180);
	shop_gradient_top = new StaticImage({ .841f + (.07f - .01875f * .5f) * 2.0f * .75f * .5f, .35f + .07f + .018f + .1f + .02075f + .01875f * .5f }, { .348f - (.07f - .01875f * .5f) * 2.0f * .75f * .5f, .105f - .01875f * .5f }, ModelHandler::getModelById(10));
	text_background = new StaticImage({ -.75f, .47f }, { .5f, .07f }, ModelHandler::getModelById(3));
	shine_rotate_left = new StaticImage({ -.725f, 0.0f }, { .4f, .4f }, ModelHandler::getModelById(4));
	shine_rotate_right = new StaticImage({ -.725f, 0.0f }, { .4f, .4f }, ModelHandler::getModelById(4));
	panel_0 = new StaticImage({ -.25f, 0 }, { .01875f, 1.0f }, ModelHandler::getModelById(9));
	panel_1 = new StaticImage({ .475f + (.07f - .01875f * .5f) * 2.0f * .75f, 0 }, { .01875f, 1.0f }, ModelHandler::getModelById(9));
	panel_2 = new StaticImage({ .84 + (.07f - .01875f * .5f) * 2.0f * .75f, .35f + .07f + .02f - .14f }, { .01875f, .35f }, ModelHandler::getModelById(9), 90.0f);
	panel_3 = new StaticImage({ .84 + (.07f - .01875f * .5f) * 2.0f * .75f, .35f + .07f + .018f + .01875f }, { .01875f, .35f }, ModelHandler::getModelById(9), 90.0f);
	shop_label = new Label("Shop", { (float) DisplayManager::width - 138.25f, DisplayManager::height - 60 }, FontHandler::getFont("kavoon", 48.0f, true), { 1.0f, 1.0f, 1.0f, 1.0f }, TextRenderer::Alignment::Center);

	renderer->button_renderer.addImageButton(button);

	renderer->static_image_renderer.addStaticImage(background2);
	renderer->static_image_renderer.addStaticImage(background1);
	renderer->static_image_renderer.addStaticImage(background);
	renderer->static_image_renderer.addStaticImage(gradient);
	renderer->static_image_renderer.addStaticImage(gradient_top);
	renderer->static_image_renderer.addStaticImage(shop_gradient_top);
	renderer->static_image_renderer.addStaticImage(text_background);
	renderer->static_image_renderer.addStaticImage(shine_rotate_left);
	renderer->static_image_renderer.addStaticImage(shine_rotate_right);
	renderer->static_image_renderer.addStaticImage(panel_0);
	renderer->static_image_renderer.addStaticImage(panel_1);
	renderer->static_image_renderer.addStaticImage(panel_2);
	renderer->static_image_renderer.addStaticImage(panel_3);

	renderer->text_renderer.addLabel(shop_label);

	threads.push_back(new std::thread(GameSaver::loop));

}

void render_header_text() {

	if (PlayerData::cookies < 1e6) {

		renderer->text_renderer.drawString(Formatter::formatCookies(PlayerData::cookies, 0) + " cookies", { 211, DisplayManager::height - 90 }, FontHandler::getFont("kavoon", 36.0f, true), { 1.0f, 1.0f, 1.0f, 1.0f }, TextRenderer::Alignment::Center);
		renderer->text_renderer.drawString("per second: " + Formatter::formatCookies(CookieHandler::get_main_cps(), 1), { 211, DisplayManager::height - 110 }, FontHandler::getFont("kavoon", 18.0f, true), { 1.0f, 1.0f, 1.0f, 1.0f }, TextRenderer::Alignment::Center);

	} else {

		renderer->text_renderer.drawString(Formatter::formatCookies(PlayerData::cookies, 0), { 211, DisplayManager::height - 80 }, FontHandler::getFont("kavoon", 20.0f, true), { 1.0f, 1.0f, 1.0f, 1.0f }, TextRenderer::Alignment::Center);
		renderer->text_renderer.drawString("cookies", { 211, DisplayManager::height - 100 }, FontHandler::getFont("kavoon", 20.0f, true), { 1.0f, 1.0f, 1.0f, 1.0f }, TextRenderer::Alignment::Center);
		renderer->text_renderer.drawString("per second: " + Formatter::formatCookies(CookieHandler::get_main_cps(), 1), { 211, DisplayManager::height - 115 }, FontHandler::getFont("kavoon", 12.0f, true), { 1.0f, 1.0f, 1.0f, 1.0f }, TextRenderer::Alignment::Center);

	}

}