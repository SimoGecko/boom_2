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
		int playerStartingHealth = 100;
		float normalMoveSpeed = 5.f;

		//bombs data
		int explosionDamage = 1;

		int nAvailableBombs = 3;
		int bombExplosionDistance = 2;
		float bombExplosionDelay = 2.5f;



		friend class Powerup;
		// ________________________________ variables


		int deployedBombs;

		// ________________________________ base
		void start() override {
			Character::start();
			restoreHealth(playerStartingHealth);
			deployedBombs = 0;
		}

		void update() override {
			Character::update();

			placeBomb();
		}

		void onCollisionEnter(GameObject& other) {
			Character::onCollisionEnter(other);

			if (other.tag() == Tag::enemy) {

			}

			if (other.tag() == Tag::explosion) {
				takeDamage(explosionDamage);
			}
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


		void placeBomb() {
			if (Input::getKeyDown(sf::Keyboard::Space)) {
				if (nAvailableBombs-deployedBombs > 0) {
					GameObject* bombGo = GameObject::Instantiate("bomb", to_v2f(currentCell()));
					deployedBombs++;
					//call back on explosion
					Bomb* bomb = bombGo->getComponent<Bomb>();
					bomb->trigger(bombExplosionDelay, bombExplosionDistance);
					bomb->onExplode += [this]() {deployedBombs--; };
				}
			}
		}

		// ________________________________ queries
		float moveSpeed() { return normalMoveSpeed; }


	};
}