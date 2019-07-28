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
		const int playerStartingHealth = 100;
		const float normalMoveSpeed = 5.f;

		//bombs data
		const int explosionDamage = 1;

		const int nAvailableBombsDefault = 3;
		const int bombExplosionDistanceDefault = 2;
		const float bombExplosionDelayDefault = 2.5f;

		int nAvailableBombs;
		int bombExplosionDistance;
		float bombExplosionDelay;
		float moveSpeed;

		friend class Powerup;
		// ________________________________ variables


		int deployedBombs;

		// ________________________________ base
		void start() override {
			Character::start();
			restoreHealth(playerStartingHealth);

			deployedBombs = 0;
			moveSpeed = normalMoveSpeed;
			nAvailableBombs = nAvailableBombsDefault;
			bombExplosionDistance = bombExplosionDistanceDefault;
			bombExplosionDelay = bombExplosionDelayDefault;
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


		// ________________________________ timed powerups
		/*
		void moreBombsEffect(int newVal, float effectDuration) {
			nAvailableBombs = newVal;
			invoke([&]() {nAvailableBombs = nAvailableBombsDefault; }, effectDuration);
		}
		void fasterBomsEffect(float newVal, float effectDuration) {
			bombExplosionDelay = newVal;
			invoke([&]() {bombExplosionDelay = bombExplosionDelayDefault; }, effectDuration);
		}
		void biggerExplosionEffect(int newVal, float effectDuration) {
			bombExplosionDistance = newVal;
			invoke([&]() {bombExplosionDistance = bombExplosionDistanceDefault; }, effectDuration);
		}

		void shieldEffect(float effectDuration) {
			setInvincible(true);
			//visual effect
			invoke([&]() {setInvincible(false); }, effectDuration);
		}
		void speedEffect(float newVal, float effectDuration) {
			moveSpeed = newVal;
			invoke([&]() {moveSpeed = normalMoveSpeed; }, effectDuration);
		}
		*/
	};
}