// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "../Engine.h"

#include "Player.h"

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
			
		}

		void onCollisionEnter(GameObject& other) {
			if (other.tag() == Tag::player) {
				Teleporter* toTeleport = getOtherRandomTeleporter();
				if (toTeleport) {
					other.getComponent<Player>()->teleport(toTeleport->transform().getPosition());
					Debug::log("teleport to");
				}
			}
		}
		
	private:
		// ______________ commands


		// ______________ queries
		Teleporter* getOtherRandomTeleporter() {
			vector<GameObject*> teleporters = GameObject::FindGameObjectsWithTag(Tag::teleporter);
			if (teleporters.size() <= 1) return nullptr;
			size_t i;
			do {
				i = Random::range(0, teleporters.size());
			} while (teleporters[i] = &gameobject());
			return teleporters[i]->getComponent<Teleporter>();
		}


		// ______________ cloning
		CLONABLE(Teleporter)
	};

}