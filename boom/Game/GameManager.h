// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "../Engine.h"

#include "GameData.h"
// manages the game state and flow (PERSISTENT)

namespace sxg::boom {

	class GameManager : public Component {
	CLONABLE(GameManager)
	public:

	private:
		// ________________________________ data
		sf::Clock timer;
		int level;
		static const int nPlayers = 1;


		// ________________________________ base
		void start() override {
			int level = 1;
			GameData::instance()->playerInfos.resize(nPlayers);
			//setup #players, resize data
			startLevel(level);
		}

		void update() override {

		}
		
		// ________________________________ commands
		void startLevel(int level) {
			//setup timer

			//show text on ui
			//Level 01\nGET READY!

			//wait....

			//instantiate map
			MapBuilder::instance()->buildLevel(level);

			//instantiate players

			//instantiate enemies
		}

		void showHurryUp() {
			//show title
		}

		void onTimerEnded() {
			//make all enemies faster
		}

		void startExtraGame() {
			//turn all into amoeba
		}

		void stopExtraGame() {
			//turn all into normal

		}

		void levelComplete() {
			//wait some time

			//notify players (thumbs up, block movement)

			//delete map and players

			//if timer>0, show timer screen

			//load next level
		}

		void timerBonus() {
			//TIME BONUS!
			//increase score iteratively

			//show title
		}

		void gameover() {
			//...
		}


		// ________________________________ queries



	};
}