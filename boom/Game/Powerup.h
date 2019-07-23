// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "../Engine.h"

#include "Pickup.h"
#include "Enemy.h"


// collectible powerup that gives special powers to the player when collected

namespace sxg::boom {

	class Powerup : public Pickup {
		CLONABLE(Powerup)
	public:
		enum PowerupType {
			flash=0,
			skull,
			moreBombs,
			fasterBombs,
			explosion,
			heart,
			hearts,
			shield,
			speed,

			SIZE
		};

	private:
		// ________________________________ data





		Animator * anim;
		PowerupType powerupType;
		// ________________________________ base
		void start() override {
			//setup powerup
			powerupType = (PowerupType)Random::range(0, PowerupType::SIZE);
			anim = gameobject().getComponent<Animator>();
			anim->playAnimation(stringFromPowerupType(powerupType));
		}

		void update() override {
		}

		
		
		// ________________________________ commands
		void pickup(Player& player) override {
			//take effect on player
			callRightEffect(player);
			gameobject().destroy();
		}

		void callRightEffect(Player& player) {
			switch (powerupType) {
				case Powerup::flash:		flashEffect(player); break;
				case Powerup::skull:		skullEffect(player); break;
				case Powerup::moreBombs:	moreBombsEffect(player); break;
				case Powerup::fasterBombs:	fasterBomsEffect(player); break;
				case Powerup::explosion:	biggerExplosionEffect(player); break;
				case Powerup::heart:		oneHeartEffect(player); break;
				case Powerup::hearts:		fullHeartsEffect(player); break;
				case Powerup::shield:		shieldEffect(player); break;
				case Powerup::speed:		speedEffect(player); break;
			}
		}

		// ________________________________ powerups

		//because no inheritance

		//what if you take multiple powerups?
		// -> MAKE SURE NO OVERLAP
		//would be better to have the player hold powerups that have effect on ctor/dtor

		void flashEffect(Player& player) {
			//destroy all blocks in the level left from right
			const float delayForOvation = 0.1f;

			vector<GameObject*> allBlocks = GameObject::FindGameObjectsWithTag(Tag::block);
			for (GameObject* block : allBlocks) {
				float delay = delayForOvation * block->transform().getPosition().x;
				block->getComponent<Block>()->breakBlock(delay);
			}
		}

		void skullEffect(Player& player) {
			//kill all enemies instantly
			vector<GameObject*> allEnemies = GameObject::FindGameObjectsWithTag(Tag::enemy);
			for (GameObject* enemy : allEnemies) {
				Enemy* e = enemy->getComponent<Enemy>();
				e->takeDamage(100); // to ensure death
			}
		}

		void moreBombsEffect(Player& player) {
			//increase the number of simultaneous bombs
			const float effectDuration = 10.f;
			const int nMaxBombsIncreased = 6;

			int currentVal = player.nAvailableBombs;
			player.nAvailableBombs = nMaxBombsIncreased;
			invoke([&]() {player.nAvailableBombs = currentVal; }, effectDuration);
		}
		void fasterBomsEffect(Player& player) {
			//decrease the bomb explosion delay
			const float effectDuration = 10.f;
			const float bombExplosionDelayShort = 1.f;

			float currentVal = player.bombExplosionDelay;
			player.bombExplosionDelay = bombExplosionDelayShort;
			invoke([&]() {player.bombExplosionDelay = currentVal; }, effectDuration);
		}
		void biggerExplosionEffect(Player& player) {
			//increase the explosion radius
			const float effectDuration = 10.f;
			const int explosionRadiusNew = 5;

			int currentVal = player.bombExplosionDistance;
			player.bombExplosionDistance = explosionRadiusNew;
			invoke([&]() {player.bombExplosionDistance = currentVal; }, effectDuration);
		}


		void oneHeartEffect(Player& player) {
			//restore one heart (2 halves) of health
			const int healAmount = 2;

			player.increaseHealth(healAmount);
		}
		void fullHeartsEffect(Player& player) {
			//restore all health
			player.restoreHealth();
		}


		void shieldEffect(Player& player) {
			//provide temporary shield effect
			const float effectDuration = 10.f;

			player.setInvincible(true);
			//visual effect
			invoke([&]() {player.setInvincible(false); }, effectDuration);
		}
		void speedEffect(Player& player) {
			//provide temporary speed boost
			const float effectDuration = 10.f;
			const float boostSpeed = 10.f;

			float currentVal = player.normalMoveSpeed;
			player.normalMoveSpeed = boostSpeed;
			invoke([&]() {player.normalMoveSpeed = currentVal; }, effectDuration);
		}


		// ________________________________ queries

		string stringFromPowerupType(PowerupType type) {
			switch (type) {
				case Powerup::flash:		return "flash";
				case Powerup::skull:		return "skull";
				case Powerup::moreBombs:	return "moreBombs";
				case Powerup::fasterBombs:	return "fasterBombs";
				case Powerup::explosion:	return "explosion";
				case Powerup::heart:		return "heart";
				case Powerup::hearts:		return "hearts";
				case Powerup::shield:		return "shield";
				case Powerup::speed:		return "speed";
			}
			return "";
		}

	};
}