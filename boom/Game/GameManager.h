// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "../Engine.h"

// manages the game state and flow (PERSISTENT)

namespace sxg::boom {

	class GameManager : public Component {
	CLONABLE(GameManager)
	public:
		static const int nPlayers = 1;

	private:
		// ________________________________ data



		// ________________________________ base
		void start() override {

		}

		void update() override {

		}
		
		// ________________________________ commands
 


		// ________________________________ queries



	};
}