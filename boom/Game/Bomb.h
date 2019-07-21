// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "../Engine.h"

// placeable bomb that explodes after some time and destroys blocks/kills enemies

namespace sxg::boom {

	class Bomb : public Component {
	private:
		// ______________ const
		const float bombTimer = 3.f;
		const float tickingOffset = 1.f;

		// ______________ variables


	public:
		// ______________ base
		void start() override {
			//Time::callback(startTicking(), bombTimer - tickingOffset);
			//Time::callback(explode(), bombTimer);
		}

		void update() override {

		}
		
	private:
		// ______________ commands
		void startTicking() {
			gameobject().getComponent<Animator>()->playAnimation("ticking");

		}

		void explode() {
			//DESTROY
			gameobject().destroy();
		}


		// ______________ queries



		// ______________ cloning
		//using Component::Component;
		Component* clone() { return new Bomb(*this); }
	};

}