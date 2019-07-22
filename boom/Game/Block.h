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
			anim->onAnimationFinish += [this]() { gameobject().destroy(); };
		}

	private:
		// ________________________________ data



		// ________________________________ base
		void start() override {

		}

		void update() override {

		}
		
		// ________________________________ commands
		



		// ________________________________ queries


	};
}