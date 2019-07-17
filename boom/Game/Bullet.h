// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "../Engine.h"

// __DESCRIPTION__

namespace sxg::boom {

	class Bullet : public Component {
	private:
		// ______________ members
		float speed = 40;

	public:
		// ______________ base
		void start() override {

		}

		void update() override {
			move();
		}
	private:
		// ______________ commands
		void move() {
			Vector2 moveDelta = Vector2(0, 1) * speed * Time::deltaTime();
			transform().move(moveDelta);
		}

		// ______________ queries




	};

}