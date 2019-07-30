// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "../Engine.h"

#include "Collectible.h"
#include "Enemy.h"


// collectible powerup that gives special powers to the player when collected

namespace sxg::boom {

	class Powerup : public Collectible {
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
		using powerupEffect = void(Powerup::*)(Player&);
		// ________________________________ data
		const float lifetime = 10.0f;
		const PointAmount myPointsOnPickup = PointAmount::p50;

		PowerupType powerupType;
		// ________________________________ base
		void start() override {
			Collectible::start();
			pointsOnPickup = myPointsOnPickup;

			powerupType = (PowerupType)Random::range(0, PowerupType::SIZE);
			anim->playAnimation(stringFromPowerupType(powerupType));

			gameobject().destroy(lifetime);
		}

		void update() override {

		}

		
		
		// ________________________________ commands
		void pickup(Player& player) override {
			//take effect on player
			powerupEffect effect = getPowerupEffect(powerupType);
			(this->*effect)(player);

			gameobject().destroy();
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
				block->getComponent<Block>()->breakBlockDelay(delay, &player);
			}
		}

		void skullEffect(Player& player) {
			//kill all enemies instantly
			vector<GameObject*> allEnemies = GameObject::FindGameObjectsWithTag(Tag::enemy);
			for (GameObject* enemy : allEnemies) {
				Enemy* e = enemy->getComponent<Enemy>();
				e->setPlayerResponsible(&player);
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


		powerupEffect getPowerupEffect(PowerupType type) {
			switch (type) {
				case Powerup::flash:		return &Powerup::flashEffect;
				case Powerup::skull:		return &Powerup::skullEffect;
				case Powerup::moreBombs:	return &Powerup::moreBombsEffect;
				case Powerup::fasterBombs:	return &Powerup::fasterBomsEffect;
				case Powerup::explosion:	return &Powerup::biggerExplosionEffect;
				case Powerup::heart:		return &Powerup::oneHeartEffect;
				case Powerup::hearts:		return &Powerup::fullHeartsEffect;
				case Powerup::shield:		return &Powerup::shieldEffect;
				case Powerup::speed:		return &Powerup::speedEffect;
			}
		}

	};
}