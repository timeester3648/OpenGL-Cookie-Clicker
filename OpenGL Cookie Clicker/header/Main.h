#pragma once

#include "display\render\Renderer.h"
#include "objects\StaticImage.h"
#include "interactable\CookieButton.h"

#include <thread>

extern Renderer* renderer;
extern std::vector<std::thread*> threads;

extern CookieButton* button;
extern StaticImage *background, *background1, *background2, *text_background;
extern StaticImage *gradient, *gradient_top, *shop_gradient_top;
extern StaticImage *shine_rotate_left, *shine_rotate_right;
extern StaticImage *panel_0, *panel_1, *panel_2, *panel_3;
extern Label* shop_label;