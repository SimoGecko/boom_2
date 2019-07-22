// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "../Engine.h"

// destroyable block that blocks the passage until broken with a bomb

namespace sxg::boom {

	class Block : public Component {
		CLONABLE(Block)
	public:
		void breakBlock() {
			Animator* anim = gameobject().getComponent<Animator>();
			anim->playAnimation("break");
			
			anim->onAnimationFinish += [this]() {
				onDestroy();
			};
			
		}

	private:
		// ________________________________ data



		// ________________________________ base
		void start() override {

		}

		void update() override {

		}
		
		// ________________________________ commands
		
		void trySpawnPowerup() {
			if (Random::value() < 0.5f) GameObject::Instantiate("powerup", transform().getPosition());
			else						GameObject::Instantiate("extra",   transform().getPosition());
		}

		void onDestroy() {
			trySpawnPowerup();
			gameobject().destroy();
		}


		// ________________________________ queries


	};
}