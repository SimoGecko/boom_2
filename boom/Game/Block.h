// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "../Engine.h"

#include "MapBuilder.h"
// destroyable block that blocks the passage until broken with a bomb

namespace sxg::boom {

	class Block : public Component {
		CLONABLE(Block)
	public:
		void breakBlockDelay(float delay = 0) {
			invoke([this]() {this->breakBlock(); }, delay);
		}

	private:
		// ________________________________ data
		const float probOfPowerup = 0.4f;
		const float probOfExtra = 0.2f;
		bool broken;

		// ________________________________ base
		void start() override {
			broken = false;
		}

		void update() override {

		}

		void onCollisionEnter (GameObject& other) override {
			if (other.tag() == Tag::explosion) breakBlock();
		}
		
		// ________________________________ commands
		void breakBlock() {
			if (broken) return;
			broken = true;
			Animator* anim = gameobject().getComponent<Animator>();
			anim->playAnimation("break");
			anim->onAnimationFinish += [this]() { onDestroy(); };
			MapBuilder::instance->blockBroke(to_v2i(transform().getPosition()));
		}

		void onDestroy() {
			trySpawnPowerup();
			gameobject().destroy();
		}

		void trySpawnPowerup() {
			if      (Random::value() < probOfPowerup) GameObject::Instantiate("powerup", transform().getPosition());
			else if (Random::value() < probOfExtra  ) GameObject::Instantiate("extra", transform().getPosition());
		}


		// ________________________________ queries


	};
}