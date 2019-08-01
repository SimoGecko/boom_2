// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "../Engine.h"

// title that is animated down

namespace sxg::boom {

	class Title : public Component {
		CLONABLE(Title)
	public:


	private:
		// ________________________________ data
		const float moveTime = 1.5f;
		const int waitTime = 1.f;

		const float maxWritingHeight = 5.f;
		const sf::Vector2f startPos = { 15.f / 2, -1.f - maxWritingHeight/2 };
		const sf::Vector2f endPos   = { 15.f / 2, 14.f + maxWritingHeight/2 };

		float progress;
		bool moving, stopped;

		// ________________________________ base
		void start() override {
			//set center sprite
			transform().setPosition(-10.f, -10.f);
			sf::Rect rect = gameobject().renderable().sprite().getTextureRect();
			gameobject().renderable().sprite().setOrigin(rect.width/2, rect.height/2);

			progress = 0.f;
			moving = true;
			stopped = false;
		}

		void update() override {
			if (moving) moveDownwards();
		}

		// ________________________________ commands
		void moveDownwards() {
			progress += Time::deltaTime() / moveTime;

			if (progress >= 0.5f && !stopped) {
				stopped = true;
				moving = false;
				invoke([this] {moving = true; }, waitTime);
			}
			if (progress > 1.0f) {
				gameobject().destroy();
			}

			transform().setPosition(lerp(startPos, endPos, progress));
		}


		// ________________________________ queries



	};
}