// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "../Engine.h"

#include "Character.h"

// AI enemy that moves around, potentially shoots and damages the player

namespace sxg::boom {

	class Enemy : public Character {
		CLONABLE(Enemy)
	public:
	
	private:
		// ________________________________ data
		//particular enemy stats here
		sf::Vector2i previousMoveDelta;
		bool mustChangeDir, canChangeDir;
		float changeDirTime = 0.2f;
		int enemyMoveSpeed = 2;
		const int explosionDamage = 1;
		const int deathAnimationTime = 3.f;

		const int enemyStartingHealth = 1;

		bool isAmoeba = false;

		// ________________________________ base
		void start() override {
			Character::start();
			restoreHealth(enemyStartingHealth);
			canChangeDir = true;
			onDeath += [this]() {enemyDie(); };
		}

		void update() override {
			Character::update();

		}

		void onCollisionEnter(GameObject& other) {
			Character::onCollisionEnter(other);

			if (other.tag() == Tag::enemy) {
				if (canChangeDir) {
					canChangeDir = false; // cooldown effect (not too frequent)
					invoke([this]() {this->canChangeDir = true; }, changeDirTime);
					mustChangeDir = true;
				}
			}

			if (other.tag() == Tag::explosion) {
				takeDamage(explosionDamage);
			}
		}
		
		// ________________________________ commands
		sf::Vector2i getInput() {
			if (mustChangeDir) { // put cooldown
				mustChangeDir = false;
				return -previousMoveDelta;
			}

			if (magnitude(moveDelta()) > 0) {
				previousMoveDelta = moveDelta();
				return { 0,0 }; // still moving, don't change dir
			}
			//stopped
			if (magnitude(previousMoveDelta)>0 && freeCell(previousMoveDelta)) return previousMoveDelta;

			//pick random available dir
			vector<sf::Vector2i> possibleDirs;
			for (sf::Vector2i d : Utility::dir4) {
				if (freeCell(d)) possibleDirs.push_back(d);
			}
			if (possibleDirs.empty()) Debug::logError("Enemy should have at least one position to move to.");
			return possibleDirs[Random::range(0, possibleDirs.size())];
		}

		void enemyDie() {
			//add score
			doMove = false;
			gameobject().destroy(deathAnimationTime);
		}

		void shoot() {
			if (Input::getMouseButtonDown(0)) {
				GameObject* bullet = GameObject::Instantiate("bullet", &transform());
				Audio::play("Shot");
			}
		}


		// ________________________________ queries

		float moveSpeed() { return enemyMoveSpeed; }

	};
}