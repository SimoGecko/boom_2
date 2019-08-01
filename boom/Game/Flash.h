// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "../Engine.h"

// teleporter flash

namespace sxg::boom {

	class Flash : public Component {
	CLONABLE(Flash)
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