// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "../Engine.h"

#include "Player.h"
#include "Points.h"

// base class for things that players can collect

namespace sxg::boom {

	class Collectible : public Component {
	public:

	protected:
		bool collected;
		Animator* anim;
		PointAmount pointsOnPickup;


		// ________________________________ data


		// ________________________________ base
		void start() override {
			collected = false;
			anim = gameobject().getComponent<Animator>();
		}

	private:
		void update() override {
		
		}

		void onCollisionEnter (GameObject& other) override {
			if (other.tag() == Tag::player) {
				if (!collected) {
					collected = true;
					Player* player = other.getComponent<Player>();
					pickup(*player);
					Points::addPoints(pointsOnPickup, transform().getPosition(), player);
				}
			}
		}
		
		// ________________________________ commands
		virtual void pickup(Player& player) = 0;

	/*
	protected:
		void addPoints(PointAmount pointsOnPickup, Player& player) { // manually call
			GameObject* pointsGo = GameObject::Instantiate("points", transform().getPosition());
			pointsGo->getComponent<Points>()->setup(pointsOnPickup, &player);
		}
		*/


		// ________________________________ queries



	};
}