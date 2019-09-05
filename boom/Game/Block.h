// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "../Engine.h"

#include "Map.h"
#include "Points.h"
//#include "Explosion.h"
#include "Living.h"

// destroyable block that blocks the passage until broken with a bomb

namespace sxg::boom {


	class Block : public Component, public Living {
		CLONABLE(Block)
	public:
		/*
		void breakBlockDelay(float delay, Player* player) {
			invoke([this, player]() {this->breakBlock(player); }, delay);
		}
		*/

	private:
		// ________________________________ data
		const float probOfPowerup = 0.4f;
		const float probOfExtra = 0.2f;
		const PointAmount pointsOnBreak = PointAmount::p10;

		bool broken;

		// ________________________________ base
		void start() override {
			broken = false;
			onDeath += [this] {breakBlock(playerResponsible); };
		}

		void update() override {

		}

		void onCollisionEnter (GameObject& other) override {
			/*
			if (other.tag() == Tag::explosion) {
				playerWhoDestroyed = other.getComponent<Explosion>()->getPlayer();//other.getComponent<Explosion>().player();
				breakBlock();
			}
			*/
		}
		
		// ________________________________ commands
		void breakBlock(Player* playerWhoDestroyed) {
			if (broken) return;
			broken = true;

			Animator* anim = gameobject().getComponent<Animator>();
			anim->playAnimation("break");
			anim->onAnimationFinish += [this]() { destroy(); };

			Map::instance()->blockBroke(to_v2i(transform().getPosition()));

			Points::addPoints(pointsOnBreak, transform().getPosition(), playerWhoDestroyed);
		}

		void destroy() {
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