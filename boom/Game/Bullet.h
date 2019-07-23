// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "../Engine.h"

// bullet that flies and damages characters

namespace sxg::boom {

	class Bullet : public Component {
		CLONABLE(Bullet)
	public:


	private:
		// ________________________________ data
		float moveSpeed = 3.f;

		// ________________________________ base
		void start() override {

		}

		void update() override {
			move();
		}

		// ________________________________ commands
		void move() {
			sf::Vector2f moveDelta = sf::Vector2f(1, 0) * moveSpeed * Time::deltaTime();
			transform().move(moveDelta);
		}

		// ________________________________ queries


	};
}