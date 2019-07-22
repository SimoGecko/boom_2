// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "../Engine.h"

#include "Pickup.h"
// collectable element that provides score

namespace sxg::boom {

	class Coin : public Pickup {
		CLONABLE(Coin)
	public:


	private:
		// ________________________________ data
		const float rotationTime = 2.f;

		// ________________________________ base
		//the most derived virtual function is called, even if class in the middle didn't re-declare as virtual
		void start() override {
			Debug::log("coin start");
		}
		

		void update() override {
			//Debug::log("coin update");

		}

		
		// ________________________________ commands
		void pickup(Player& player) override {
			Debug::log("called");
			Animator* anim = gameobject().getComponent<Animator>();
			anim->playAnimation("rotate");
			//add to score manager
			MapBuilder::instance->removeGo(to_v2i(transform().getPosition()));
			gameobject().destroy(rotationTime);
		}

		// ________________________________ queries



	};
}