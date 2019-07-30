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
		void setPlayerResponsible(Player* player) { damageResponsiblePlayer = player; }

		static int numRemainingEnemies() { return nEnemies; }
		static Event onAllEnemiesDefeated;

		void setAmeba(bool active) {
			isAmoeba = active;
		}

	private:
		// ________________________________ data
		//particular enemy stats here
		const float changeDirTime = 0.2f;
		const float enemyMoveSpeed = 2;

		const float raycastQueryDelay = 0.5f;
		const float shootCooldown = 3.0f;

		const int deathAnimationTime = 3.f;
		const int enemyStartingHealth = 1;
		const PointAmount myPointsOnDeath = PointAmount::p200;

		static int nEnemies;

		sf::Vector2i previousMoveDelta;
		bool canChangeDir;
		bool mustChangeDir;

		bool canShoot;
		bool playerInFront;

		bool isAmoeba;

		// ________________________________ base
		void start() override {
			Character::start();
			nEnemies++;
			
			restoreHealth(enemyStartingHealth);
			canChangeDir = true;
			onDeath += [this]() {enemyDie(); };
		}

		void update() override {
			Character::update();

			if (wantsToShoot()) {
				shoot();
			}
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
		}
		
		// ________________________________ commands
		sf::Vector2i getInput() {
			if (mustChangeDir) { // put cooldown
				mustChangeDir = false;
				return -previousMoveDelta;
			}

			if (magnitude1(moveDelta()) > 0) {
				previousMoveDelta = moveDelta();
				return { 0,0 }; // still moving, don't change dir
			}
			//stopped
			if (magnitude1(previousMoveDelta)>0 && freeCell(previousMoveDelta)) return previousMoveDelta;

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
			Points::addPoints(myPointsOnDeath, transform().getPosition(), damageResponsiblePlayer);

			//check if last
			if (--nEnemies == 0) onAllEnemiesDefeated();

			gameobject().destroy(deathAnimationTime);
		}

		void shoot() {
			GameObject* bullet = GameObject::Instantiate("bullet", &transform());
			Audio::play("Shot");
		}

		void queryPlayerInFront() {
			playerInFront = playerInFrontRaycast();
			invoke([this] {queryPlayerInFront(); }, raycastQueryDelay);
		}


		// ________________________________ queries
		bool wantsToShoot() {
			return canShoot && !isAmoeba && playerInFront;
		}

		bool playerInFrontRaycast() {
			//primitive raycast

		}

		float moveSpeed() { return enemyMoveSpeed; }

	};
}