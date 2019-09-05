// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "../Engine.h"

#include "Character.h"

// on contact with a character, it teleports it to the next instance of a teleporter

namespace sxg::boom {

	class Teleporter : public Component {
		CLONABLE(Teleporter)
	public:
		
	
	private:
		// ________________________________ data

		// ________________________________ base
		void start() override {

		}

		void update() override {
			
		}

		void onCollisionEnter(GameObject& other) {
			Character* character = other.getComponent<Character>();
			if (character!=nullptr && character->canTeleport()) {
				Teleporter* toTeleport = getOtherRandomTeleporter();
				if (toTeleport) {
					playEffect(transform().getPosition());
					character->teleport(toTeleport->transform().getPosition());
					playEffect(toTeleport->transform().getPosition());
				}
			}
		}
		
		// ________________________________ commands
		void playEffect(sf::Vector2f position) {
			GameObject* effectGo = GameObject::Instantiate("flash", position);
			//effectGo->destroy(2.f);
		}


		// ________________________________ queries
		Teleporter* getOtherRandomTeleporter() {
			vector<GameObject*> teleporters = GameObject::FindGameObjectsWithTag(Tag::teleporter);
			if (teleporters.size() <= 1) return nullptr;
			int i;
			do {
				i = Random::range(0, teleporters.size());
			} while (teleporters[i] == &gameobject());
			return teleporters[i]->getComponent<Teleporter>();
		}

	};
}