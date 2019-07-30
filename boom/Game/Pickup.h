// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "../Engine.h"

#include "Player.h"
#include "Points.h"

// base class for things that players can collect

namespace sxg::boom {

	class Pickup : public Component {
	public:

	protected:
		PointAmount pointsOnPickup;

	private:
		// ________________________________ data



		// ________________________________ base
		void start() override { } // skipped

		void update() override { }

		void onCollisionEnter (GameObject& other) override {
			if (other.tag() == Tag::player) pickup(*other.getComponent<Player>());
		}
		
		// ________________________________ commands
		virtual void pickup(Player& player) = 0;

		void addPoints(Player& player) {
			GameObject* pointsGo = GameObject::Instantiate("points", transform().getPosition());
			pointsGo->getComponent<Points>()->setup(pointsOnPickup, &player);
		}


		// ________________________________ queries



	};
}