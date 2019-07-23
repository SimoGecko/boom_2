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
		bool mustChangeDir;

		// ________________________________ base
		void start() override {
			Character::start();
			moveSpeed = 2;
			startingHealth = 1;
		}

		void update() override {
			Character::update();

		}

		void onCollisionEnter(GameObject& other) {
			Character::onCollisionEnter(other);

			if (other.tag() == Tag::enemy) {
				//change dir (hopefully just once)
				mustChangeDir = true;
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
			if (freeCell(sf::Vector2i( 1, 0))) possibleDirs.push_back(sf::Vector2i( 1, 0));
			if (freeCell(sf::Vector2i(-1, 0))) possibleDirs.push_back(sf::Vector2i(-1, 0));
			if (freeCell(sf::Vector2i(0,  1))) possibleDirs.push_back(sf::Vector2i(0,  1));
			if (freeCell(sf::Vector2i(0, -1))) possibleDirs.push_back(sf::Vector2i(0, -1));
			if (possibleDirs.empty()) Debug::logError("Enemy should have at least one position to move to.");
			return possibleDirs[Random::range(0, possibleDirs.size())];
		}


		// ________________________________ queries



	};
}