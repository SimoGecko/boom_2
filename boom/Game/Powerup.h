// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "../Engine.h"

// collectible powerup that gives special powers to the player when collected

namespace sxg::boom {

	class Powerup : public Component {
		CLONABLE(Powerup)
	public:

	private:
		// ________________________________ data


		// ________________________________ base
		void start() override {

		}

		void update() override {

		}

		enum PowerupType {

		};
		
		// ________________________________ commands
 

		// ________________________________ queries



	};
}