// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "../Engine.h"

#include "MapBuilder.h"

// the graphic effect of an explosion

namespace sxg::boom {

	class Explosion : public Component {
		CLONABLE(Explosion)
	public:

	private:
		// ________________________________ data


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