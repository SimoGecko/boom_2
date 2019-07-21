// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "../Engine.h"

#include "MapBuilder.h"

// the graphic effect of an explosion

namespace sxg::boom {

	class Explosion : public Component {
	private:
		// ______________ members


	public:
		// ______________ base
		void start() override {
			damageComponents();
			deleteOnAnimationFinish();
		}

		void update() override {

		}
		
	private:
		// ______________ commands
		void damageComponents() {
			MapBuilder::instance->explosionAt(to_v2i(transform().getPosition()));
		}

		void deleteOnAnimationFinish() {
			gameobject().getComponent<Animator>()->onAnimationFinish += [this]() { gameobject().destroy(); };
		}

		// ______________ queries



		// ______________ cloning
		//using Component::Component;
		Component* clone() { return new Explosion(*this); }

	};

}