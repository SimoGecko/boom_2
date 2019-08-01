// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "../Engine.h"

#include "Collectible.h"
// collectable element that provides score

namespace sxg::boom {

	class Coin : public Collectible {
		CLONABLE(Coin)
	public:
		//static int numRemainingCoins() { return nCoins; }
		static Event onAllCoinsCollected;


	private:
		// ________________________________ data
		const float rotationTime = 2.f;
		const Points::Amount myPointsOnPickup = Points::Amount::p150;

		static int nCoins;

		// ________________________________ base
		//the most derived virtual function is called, even if class in the middle didn't re-declare as virtual
		void start() override {
			Collectible::start();
			pointsOnPickup = myPointsOnPickup;

			nCoins++;
		}
		

		void update() override {

		}

		
		// ________________________________ commands
		void pickup(Player& player) override {
			anim->playAnimation("rotate");

			//check if last, to trigger special stuff
			if (--nCoins == 0) onAllCoinsCollected();

			gameobject().destroy(rotationTime);
		}


		// ________________________________ queries

	};
}