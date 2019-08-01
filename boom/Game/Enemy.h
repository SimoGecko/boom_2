// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "../Engine.h"

#include "Character.h"
#include "Points.h"

// AI enemy that moves around, potentially shoots and damages the player

namespace sxg::boom {

	class Enemy : public Character {
		CLONABLE(Enemy)
	public:
		enum class Type {
			amoeba = 20,
			soldier = 0,
			sarge,
			lizzy,
			taur,
			gunner,
			thing,
			ghost,
			smoulder,
			skully,
			giggler,

			SIZE
		};

		static Event onAllEnemiesDefeated;

		void setAmeba(bool active) {
			isAmoeba = active;
		}
		void speedUp() {
			//TODO
		}

		void setup(Type type) {

		}

		

	private:
		// ________________________________ data
		//particular enemy stats here
		const float changeDirTime = 0.2f;
		const float enemyMoveSpeed = 2;

		const int damage = 1; // if const is not initialized compiler prohibits instantiation

		const float raycastQueryDelay = 0.5f;
		const float shootCooldown = 3.0f;

		const int deathAnimationTime = 3.f;
		const int enemyStartingHealth = 1;
		const Points::Amount myPointsOnDeath = Points::Amount::p200;

		static int nEnemies;

		sf::Vector2i previousMoveDelta;
		bool canChangeDir;
		bool mustChangeDir;

		bool canShoot;
		bool playerInFront;

		bool isAmoeba;
		Type enemyType;

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

			if (other.tag() == Tag::player) {
				other.getComponent<Living>()->takeDamage(damage);
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
			canMove = false;
			Points::addPoints(myPointsOnDeath, transform().getPosition(), _responsiblePlayer);

			if (isAmoeba) {
				GameObject::Instantiate("extra", transform().getPosition());
			}

			Audio::play("enemy/" + stringFromType(enemyType) + "_death");

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

		const string stringFromType(Type type) {
			switch (type) {
				case Type::amoeba:		return "amoeba";
				case Type::soldier:		return "soldier";
				case Type::sarge:		return "sarge";
				case Type::lizzy:		return "lizzy";
				case Type::taur:		return "taur";
				case Type::gunner:		return "gunner";
				case Type::thing:		return "thing";
				case Type::ghost:		return "ghost";
				case Type::smoulder:	return "smoulder";
				case Type::skully:		return "skully";
				case Type::giggler:		return "giggler";
			}
			return "";
		}

	};
}