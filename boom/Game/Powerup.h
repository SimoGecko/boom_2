// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "../Engine.h"

#include "Pickup.h"

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

		void flashEffect(Player& player) {
			//destroy all blocks in the level left from right
		}
		void skullEffect(Player& player) {
			//kill all enemies instantly
		}
		void moreBombsEffect(Player& player) {
			//increase the number of simultaneous bombs
		}
		void fasterBomsEffect(Player& player) {
			//decrease the bomb explosion delay
		}
		void biggerExplosionEffect(Player& player) {
			//increase the explosion radius
		}
		void oneHeartEffect(Player& player) {
			//restore one heart of health
		}
		void fullHeartsEffect(Player& player) {
			//restore all health

		}
		void shieldEffect(Player& player) {
			//provide temporary shield effect

		}
		void speedEffect(Player& player) {
			//provide temporary speed boost

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