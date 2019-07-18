// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "../Engine.h"

// prototypical class to move player around

namespace sxg::boom {

	class Player : public Component {
	private:
		// ______________ members
		float speed = 30.f;

	public:
		// ______________ base
		void start() override {
			//transform().setPosition(0, 0);
		}

		void update() override {
			//Debug::Log("updating");
			
			movement();
			shoot();
			
		}
	private:
		// ______________ commands
		void movement() {
			Vector2 input;
			if (Input::getKey(sf::Keyboard::A)) input.x -= 1;
			if (Input::getKey(sf::Keyboard::D)) input.x += 1;
			if (Input::getKey(sf::Keyboard::W)) input.y -= 1;
			if (Input::getKey(sf::Keyboard::S)) input.y += 1;

			Vector2 moveDelta = normalize(input) * speed * Time::deltaTime();

			transform().move(moveDelta);
		}

		void shoot() {
			if (Input::getKeyDown(sf::Keyboard::Space)) {
				//instantiate new bullet at this position
				Debug::Log("shoot");
				GameObject* bullet = GameObject::Instantiate("bullet", &transform());
			}
		}

		// ______________ queries

		using Component::Component; // must inherit ctor
	};

}