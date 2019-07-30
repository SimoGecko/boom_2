// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "../Engine.h"

#include "MapBuilder.h"
#include "Points.h"
#include "Explosion.h"

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
		const PointAmount pointsOnBreak = PointAmount::p10;

		bool broken;
		Player* playerWhoDestroyed;

		// ________________________________ base
		void start() override {
			broken = false;
			playerWhoDestroyed = nullptr;
		}

		void update() override {

		}

		void onCollisionEnter (GameObject& other) override {
			if (other.tag() == Tag::explosion) {
				playerWhoDestroyed = other.getComponent<Explosion>()->player();//other.getComponent<Explosion>().player();
				breakBlock();
			}
		}
		
		// ________________________________ commands
		void breakBlock() {
			if (broken) return;
			broken = true;

			Animator* anim = gameobject().getComponent<Animator>();
			anim->playAnimation("break");
			anim->onAnimationFinish += [this]() { gameobject().destroy(); };

			MapBuilder::instance->blockBroke(to_v2i(transform().getPosition()));

			addPoints();
			trySpawnPowerup();
		}


		void trySpawnPowerup() {
			if      (Random::value() < probOfPowerup) GameObject::Instantiate("powerup", transform().getPosition());
			else if (Random::value() < probOfExtra  ) GameObject::Instantiate("extra", transform().getPosition());
		}

		//repeated from
		void addPoints() {
			GameObject* pointsGo = GameObject::Instantiate("points", transform().getPosition());
			pointsGo->getComponent<Points>()->setup(pointsOnBreak, playerWhoDestroyed);
		}


		// ________________________________ queries


	};
}