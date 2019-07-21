// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "../Engine.h"

// bullet that flies and damages characters

namespace sxg::boom {

	class Bullet : public Component {
	private:
		// ______________ members
		float speed = 3;

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
			sf::Vector2f moveDelta = sf::Vector2f(1, 0) * speed * Time::deltaTime();
			transform().move(moveDelta);
		}

		// ______________ queries


		// ______________ cloning
		//using Component::Component;
		Component* clone() { return new Bullet(*this); }
	};

}