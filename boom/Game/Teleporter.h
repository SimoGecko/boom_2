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
			
			if (Input::getKeyDown(sf::Keyboard::Q)){
				gameobject().getComponent<Animator>()->playAnimation("default");
			}
			
		}
		
	private:
		// ______________ commands


		// ______________ queries
		Teleporter* getOtherRandomTeleporter() {
			vector<GameObject*> teleporters = GameObject::FindGameObjectsWithTag(Tag::teleporter);
			size_t i;
			do {
				i = Random::range(0, teleporters.size());
			} while (teleporters[i] = &gameobject());
			return teleporters[i]->getComponent<Teleporter>();
		}


		// ______________ cloning
		//using Component::Component;
		Component* clone() { return new Teleporter(*this); }
	};

}