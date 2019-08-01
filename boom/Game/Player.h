// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "../Engine.h"

#include "Character.h"
#include "Bomb.h"
#include "GameData.h"
#include "Shield.h"

// prototypical class to move player around

namespace sxg::boom {

	class Player : public Character {
		CLONABLE(Player)
	public:

		void setPlayerIdx(int index) {
			//setup player-index specifics
			playerIndex = index;
			info = &GameData::instance()->playerInfos[playerIndex];
			//set color
			const sf::Texture& playerTexture = Resources::Get<sf::Texture>("player/player_" + to_string(index + 1));
			gameobject().renderable().sprite().setTexture(playerTexture);
		}
		void addScore(int score) { info->score += score; }

		void collectLetter(int letter) {
			info->extra[letter] = true;
			checkIfAllExtraLetters();
		}

		void notifyEnd() {
			canMove = false;
			//play happy sound
			anim->playAnimation("win");
			Audio::play("player/p" + to_string(playerIndex + 1) + "_complete");
		}

		void activateShield(bool b) {
			setInvincible(b);
			shield->turnOn(b);
		}

	private:
		// ________________________________ const
		int playerStartingHealth = 16;
		float normalMoveSpeed = 5.f;

		//bombs data

		int nAvailableBombs = 3;
		int bombExplosionDistance = 2;
		float bombExplosionDelay = 2.5f;


		friend class Powerup;
		// ________________________________ variables

		int playerIndex = 0;
		playerInfo* info;
		Shield* shield;
		int deployedBombs;

		// ________________________________ base
		void start() override {
			Character::start();
			restoreHealth(playerStartingHealth);
			deployedBombs = 0;
			
			onDamage	   += [this]() {onPlayerDamage(); };
			onHealthChange += [this]() {onPlayerChangeHealth(); };
			onDeath		   += [this]() {onPlayerDeath(); };

			GameObject* shieldGo = GameObject::Instantiate("shield");
			//shield = shieldGo->getComponent<Shield>();
		}

		void update() override {
			Character::update();

			if(bombInput() && canPlaceBomb()) placeBomb();
			//updateShield();
		}

		void onCollisionEnter(GameObject& other) override {
			Character::onCollisionEnter(other);

		}

		
		// ________________________________ commands
		
		void updateShield() {
			shield->setDir(moveDir());
			shield->transform().setPosition(transform().getPosition());
		}

		sf::Vector2i getInput() {
			sf::Vector2i input;
			if (playerIndex == 0) {
				if (Input::getKey(sf::Keyboard::A)) input.x -= 1;
				if (Input::getKey(sf::Keyboard::D)) input.x += 1;
				if (Input::getKey(sf::Keyboard::W)) input.y -= 1;
				if (Input::getKey(sf::Keyboard::S)) input.y += 1;
			}
			else if (playerIndex == 1) {
				if (Input::getKey(sf::Keyboard::Left))  input.x -= 1;
				if (Input::getKey(sf::Keyboard::Right)) input.x += 1;
				if (Input::getKey(sf::Keyboard::Up))    input.y -= 1;
				if (Input::getKey(sf::Keyboard::Down))  input.y += 1;
			}

			return input;
		}


		void placeBomb() {
			deployedBombs++;
			GameObject* bombGo = GameObject::Instantiate("bomb", to_v2f(currentCell()));
			//call back on explosion
			Bomb* bomb = bombGo->getComponent<Bomb>();
			bomb->dropBomb(bombExplosionDelay, bombExplosionDistance, this);
			bomb->onExplode += [this]() {deployedBombs--; };
		}

		void onPlayerDamage() {
			Audio::play("player/p" + to_string(playerIndex+1) + "_ouch");
			shield->blink();
		}

		void onPlayerChangeHealth() {
			info->halfHearts = health();

		}

		void onPlayerDeath() {
			Audio::play("player/p" + to_string(playerIndex + 1) + "_death");
			//reduce lives

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

		bool bombInput() {
			if (playerIndex == 0) return Input::getKeyDown(sf::Keyboard::Space);
			if (playerIndex == 1) return Input::getKeyDown(sf::Keyboard::Enter);
			return false;
		}

		bool canPlaceBomb() {
			return (nAvailableBombs - deployedBombs > 0) && true /*not bomb already there*/;
		}


	};
}