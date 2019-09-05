// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "../Engine.h"

#include "Collectible.h"
#include "Living.h"
//#include "Enemy.h"
//#include "Block.h"


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
		// ________________________________ const
		const float lifetime = 10.0f;
		const Points::Amount myPointsOnPickup = Points::Amount::p50;

		const float effectDuration = 10.f;

		const float delayForOvation = 0.1f;
		const float boostSpeed = 10.f;
		const float skullDamage = 1;
		const int nMaxBombsIncreased = 6;
		const float bombExplosionDelayShort = 1.f;
		const int healAmount = 2;
		const int explosionRadiusNew = 5;







		// ________________________________ data


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
			vector<GameObject*> allBlocks = GameObject::FindGameObjectsWithTag(Tag::block);
			for (GameObject* blockGo : allBlocks) {
				float delay = delayForOvation * blockGo->transform().getPosition().x;
				Living* block = blockGo->getComponent<Living>();
				Player* pl = &player;
				Time::invoke([=] {block->takeDamage(1, pl); }, delay, blockGo);
			}
		}

		void skullEffect(Player& player) {
			//kill all enemies instantly
			vector<GameObject*> allEnemies = GameObject::FindGameObjectsWithTag(Tag::enemy);
			for (GameObject* enemy : allEnemies) {
				enemy->getComponent<Living>()->takeDamage(skullDamage, &player);
			}
		}

		void moreBombsEffect(Player& player) {
			//increase the number of simultaneous bombs
			int currentVal = player.nAvailableBombs;
			player.nAvailableBombs = nMaxBombsIncreased;
			Time::invoke([&]() {player.nAvailableBombs = currentVal; }, effectDuration, &player.gameobject());
		}
		void fasterBomsEffect(Player& player) {
			//decrease the bomb explosion delay
			float currentVal = player.bombExplosionDelay;
			player.bombExplosionDelay = bombExplosionDelayShort;
			Time::invoke([&]() {player.bombExplosionDelay = currentVal; }, effectDuration, &player.gameobject());
		}
		void biggerExplosionEffect(Player& player) {
			//increase the explosion radius
			int currentVal = player.bombExplosionDistance;
			player.bombExplosionDistance = explosionRadiusNew;
			Time::invoke([&]() {player.bombExplosionDistance = currentVal; }, effectDuration, &player.gameobject());
		}


		void oneHeartEffect(Player& player) {
			//restore one heart (2 halves) of health
			player.increaseHealth(healAmount);
		}
		void fullHeartsEffect(Player& player) {
			//restore all health
			player.restoreHealth();
		}


		void shieldEffect(Player& player) {
			//provide temporary shield effect
			player.activateShield(true);
			//visual effect
			Time::invoke([&]() {player.activateShield(false); }, effectDuration, &player.gameobject());
		}
		void speedEffect(Player& player) {
			//provide temporary speed boost
			float currentVal = player.normalMoveSpeed;
			player.normalMoveSpeed = boostSpeed;
			Time::invoke([&]() {player.normalMoveSpeed = currentVal; }, effectDuration, &player.gameobject());
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