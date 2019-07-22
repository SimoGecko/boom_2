// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "../Engine.h"

#include "Player.h"

// base class for things that players can collect

namespace sxg::boom {

	class Pickup : public Component {
	public:


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


		// ________________________________ queries



	};
}