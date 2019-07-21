// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "../Engine.h"

// AI enemy that moves around, potentially shoots and damages the player

namespace sxg::boom {

	class Enemy : public Component {
	private:
		// ______________ members


	public:
		// ______________ base
		void start() override {

		}

		void update() override {

		}
		
	private:
		// ______________ commands
 

		// ______________ queries



		// ______________ cloning
		Component* clone() { return new Enemy(*this); }
	};

}