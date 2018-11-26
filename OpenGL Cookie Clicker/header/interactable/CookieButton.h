#pragma once

#include "ImageButton.h"
#include "../sound/Sound.h"

#include <vector>

class CookieButton : public ImageButton {

	private:

		Vec2 start_dim;
		std::vector<Sound*> sounds;

	public:

		CookieButton(Vec2 position, Vec2 scale);
		~CookieButton();

	private:

		void play_random();

	public:

		virtual void activate() override;
		virtual void update() override;
		virtual void onMouseUp(int key) override;
		virtual void onMouseDown(int key) override;

		virtual bool over(double x, double y) override;

};