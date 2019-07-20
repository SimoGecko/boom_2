// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "../Engine.h"

// on contact with a character, it teleports it to the next instance of a teleporter

namespace sxg::boom {

	class Teleporter : public Component {
	private:
		// ______________ members


	public:
		// ______________ base
		void start() override {

		}

		void update() override {
			/*
			if (Input::getKeyDown(sf::Keyboard::Q)){
				gameobject().getComponent<Animator>()->playAnimation("default");
			}
			*/
		}
		
	private:
		// ______________ commands


		// ______________ queries



		// ______________ cloning
		using Component::Component;
		Teleporter* clone(GameObject& go) override { return new Teleporter(go); }

	};

}