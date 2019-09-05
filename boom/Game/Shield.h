// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "../Engine.h"

// shield for player (visual effect)

namespace sxg::boom {

	class Shield : public Component {
	CLONABLE(Shield)
	public:
		void turnOn(bool b) {
			on = b;
		}
		void blink() {
			blinking = true;
			invoke([this] {blinking = false; }, blinkDuration);
		}
		void setDir(dir newDir) {
			shieldDir = newDir;
		}

	private:
		// ________________________________ data
		const float blinkDuration = 2.f;
		const float blindFrequency = 3.f;

		Animator* anim;

		dir shieldDir;
		
		bool on;
		bool blinking;

		// ________________________________ base
		void start() override {
			anim = gameobject().getComponent<Animator>();
		}

		void update() override {
			//setAnimation();
		}
		
		// ________________________________ commands
		void setAnimation() {
			string animName = "empty";
			if (on || (blinking && rightTime())) {
				animName = "shield_" + string(1, charFromDir(shieldDir));
			}

			if (animName != anim->currentAnimationName()) {
				anim->playAnimation(animName);
			}
		}


		// ________________________________ queries
		bool rightTime() {
			return (int)(Time::time() * blindFrequency) % 2 == 0;
		}


	};
}