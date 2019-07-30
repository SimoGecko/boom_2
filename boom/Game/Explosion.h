// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "../Engine.h"

#include "MapBuilder.h"

// the graphic effect of an explosion

namespace sxg::boom {

	class Player;

	class Explosion : public Component {
		CLONABLE(Explosion)
	public:
		Player* player() const { return owner; }
		void setPlayer(Player* player) { owner = player; }

	private:
		// ________________________________ data
		Player* owner;

		// ________________________________ base
		void start() override {
			deleteOnAnimationFinish();
		}

		void update() override {
		
		}
		
		// ________________________________ commands

		void deleteOnAnimationFinish() {
			gameobject().getComponent<Animator>()->onAnimationFinish += [this]() { gameobject().destroy(); };
		}

		// ________________________________ queries



	};
}