// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "../Engine.h"

// collectible powerup that gives special powers to the player when collected

namespace sxg::boom {

	class Powerup : public Component {
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
		CLONABLE(Powerup)
	};

}