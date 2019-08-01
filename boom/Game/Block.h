// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "../Engine.h"

#include "Map.h"
#include "Points.h"
//#include "Explosion.h"

// destroyable block that blocks the passage until broken with a bomb

namespace sxg::boom {

	class Block : public Component, public Living {
		CLONABLE(Block)
	public:
		/*
		void breakBlockDelay(float delay, Player* player) {
			playerWhoDestroyed = player;
			invoke([this]() {this->breakBlock(); }, delay);
		}
		*/

	private:
		// ________________________________ data
		const float probOfPowerup = 0.1f;
		const Points::Amount pointsOnBreak = Points::Amount::p10;


		// ________________________________ base
		void start() override {
			onDeath += [this] {breakBlock(); };
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
		void breakBlock() {
			Animator* anim = gameobject().getComponent<Animator>();
			anim->playAnimation("break");
			anim->onAnimationFinish += [this]() { destroy(); };

			Map::instance()->blockBroke(to_v2i(transform().getPosition()));

			Points::addPoints(pointsOnBreak, transform().getPosition(), _responsiblePlayer);
		}

		void destroy() {
			trySpawnPowerup();
			gameobject().destroy();
		}


		void trySpawnPowerup() {
			if (Random::value() < probOfPowerup) GameObject::Instantiate("powerup", transform().getPosition());
		}


		// ________________________________ queries


	};
}