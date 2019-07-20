// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "../Engine.h"

// prototypical class to move player around

namespace sxg::boom {

	class Player : public Component {
	private:
		// ______________ members
		float speed = 6.f;
		Animator* anim;

	public:
		// ______________ base
		void start() override {
			//transform().setPosition(0, 0);
			anim = gameobject().getComponent<Animator>();
		}

		void update() override {
			movement();
			shoot();
			//setAnimation();
			if (Input::getKeyDown(sf::Keyboard::Q)) {
				anim->playAnimation("front_walk");
			}
			Gizmos::drawCircle(transform().getPosition(), 0.5f);
		}
	private:
		// ______________ commands
		void movement() {
			vector2 input;
			if (Input::getKey(sf::Keyboard::A)) input.x -= 1;
			if (Input::getKey(sf::Keyboard::D)) input.x += 1;
			if (Input::getKey(sf::Keyboard::W)) input.y -= 1;
			if (Input::getKey(sf::Keyboard::S)) input.y += 1;
			// can only move in one direction

			vector2 moveDelta = normalize(input) * speed * Time::deltaTime();
			transform().move(moveDelta);
		}

		void setAnimation(vector2 input) {
			bool moving = magnitude2(input) > 0;

		}

		void shoot() {
			if (Input::getKeyDown(sf::Keyboard::Space)) {
				//instantiate new bullet at this position
				GameObject* bullet = GameObject::Instantiate("bullet", &transform());
				Audio::play("Shot");
			}
		}

		// ______________ queries

		using Component::Component; // must inherit ctor
	};

}