// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "../Engine.h"

#include "Character.h"
#include "Bomb.h"
#include "Score.h"

// prototypical class to move player around

namespace sxg::boom {

	class Player : public Character {
		CLONABLE(Player)
	public:
		void teleport(sf::Vector2f to) {
			//wait to stop
		}
		void setPlayerIndex(int index) {
			playerIndex = index;
			setupPlayer();
		}
		void addScore(int score) { info->score += score; }

		void collectLetter(int letter) {
			info->extra[letter] = true;
			checkIfAllExtraLetters();
		}

	private:
		// ________________________________ const
		const int playerStartingHealth = 16;
		const float normalMoveSpeed = 5.f;

		//bombs data

		const int nAvailableBombs = 3;
		const int bombExplosionDistance = 2;
		const float bombExplosionDelay = 2.5f;


		friend class Powerup;
		// ________________________________ variables

		int playerIndex;
		playerInfo* info;
		int deployedBombs;

		// ________________________________ base
		void start() override {
			Character::start();
			restoreHealth(playerStartingHealth);
			deployedBombs = 0;
			
			onHealthChange += [this]() {onPlayerDamage(); };
			
			

		}

		void update() override {
			Character::update();

			placeBomb();
		}

		void onCollisionEnter(GameObject& other) override {
			Character::onCollisionEnter(other);

			if (other.tag() == Tag::enemy) {

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

		void setupPlayer() {
			//setup player-index specifics
			info = &Score::instance()->playerInfos[playerIndex];
		}


		void placeBomb() {
			if (Input::getKeyDown(sf::Keyboard::Space)) {
				if (nAvailableBombs-deployedBombs > 0) {
					deployedBombs++;
					GameObject* bombGo = GameObject::Instantiate("bomb", to_v2f(currentCell()));
					//call back on explosion
					Bomb* bomb = bombGo->getComponent<Bomb>();
					bomb->dropBomb(bombExplosionDelay, bombExplosionDistance, this);
					bomb->onExplode += [this]() {deployedBombs--; };
				}
			}
		}

		void onPlayerDamage() {
			info->halfHearts = health();
		}

		void checkIfAllExtraLetters() {
			bool hasAll = true;
			for (bool b : info->extra) hasAll = hasAll && b;
			if (hasAll) {
				for (size_t i = 0; i < info->extra.size(); ++i) info->extra[i]=false;
				//add life

				//instantiate stuff
			}
		}

		// ________________________________ queries
		float moveSpeed() { return normalMoveSpeed; }


	};
}