// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "../Engine.h"

//#include "Map.h"

// the graphic effect of an explosion

namespace sxg::boom {

	class Player;

	class Explosion : public Component {
		CLONABLE(Explosion)
	public:
		void setup(Player* p, sf::Vector2f origin) {
			player = p;
			bombOrigin = origin;
		}

		Player* getPlayer() { return player; }
		sf::Vector2f getOrigin() { return bombOrigin; }

	private:
		// ________________________________ data
		Player* player;
		sf::Vector2f bombOrigin;

		// ________________________________ base
		void start() override {
			deleteOnAnimationFinish();
		}

		void update() override {
		
		}

		void onCollisionEnter(GameObject& other) override {
			Living* living = other.getComponent<Living>();
			if (living != nullptr) {
				living->takeDamage(1, player);
			}
		}
		
		// ________________________________ commands

		void deleteOnAnimationFinish() {
			gameobject().getComponent<Animator>()->onAnimationFinish += [this]() { gameobject().destroy(); };
		}

		// ________________________________ queries



	};
}