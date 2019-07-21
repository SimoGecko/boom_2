// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "../Engine.h"

// collectable element that provides score

namespace sxg::boom {

	class Coin : public Component {
	private:
		// ______________ members
		const float rotationTime = 2.f;

	public:
		// ______________ base
		void start() override {

		}

		void update() override {

		}

		void onCollisionEnter(const GameObject& other) override {
			if (other.tag() == Tag::player) {
				collectCoin();
			}
		}
		
	private:
		// ______________ commands
		void collectCoin() {
			Animator* anim = gameobject().getComponent<Animator>();
			anim->playAnimation("rotate");
			//add to score manager
			MapBuilder::instance->removeGo(to_v2i(transform().getPosition()));
			gameobject().destroy(rotationTime);
		}

		// ______________ queries



		// ______________ cloning
		//using Component::Component;
		Component* clone() { return new Coin(*this); }

	};

}