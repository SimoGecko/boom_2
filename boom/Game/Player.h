// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "../Engine.h"

#include "Character.h"
#include "Bomb.h"

// prototypical class to move player around

namespace sxg::boom {

	class Player : public Character {
		CLONABLE(Player)
	public:
		void teleport(sf::Vector2f to) {
			//wait to stop
		}
	private:
		// ________________________________ const
		const float speedBoost = 2.f;

		const int nMaxBombs = 3;
		const int nMaxBombsPowerup = 6;

		// ________________________________ variables


		int availableBombs;

		// ________________________________ base
		void start() override {
			Character::start();

			availableBombs = nMaxBombs;
		}

		void update() override {
			Character::update();

			placeBomb();
		}

		
		// ________________________________ commands
		

		sf::Vector2i getInput() {
			sf::Vector2i input;
			if (Input::getKey(sf::Keyboard::A)) input.x -= 1;
			if (Input::getKey(sf::Keyboard::D)) input.x += 1;
			if (Input::getKey(sf::Keyboard::W)) input.y -= 1;
			if (Input::getKey(sf::Keyboard::S)) input.y += 1;
			return input;
		}
		

		

		void shoot() {
			if (Input::getMouseButtonDown(0)) {
				GameObject* bullet = GameObject::Instantiate("bullet", &transform());
				Audio::play("Shot");
			}
		}

		void placeBomb() {
			if (Input::getKeyDown(sf::Keyboard::Space)) {
				if (availableBombs > 0) {
					GameObject* bombGo = GameObject::Instantiate("bomb", to_v2f(currentCell()));
					availableBombs--;
					//call back on explosion
					bombGo->getComponent<Bomb>()->onExplode += [this]() {availableBombs++; };
				}
			}
		}

		// ________________________________ queries


	};
}