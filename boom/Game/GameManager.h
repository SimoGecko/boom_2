// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "../Engine.h"

#include "GameData.h"
// manages the game state and flow (PERSISTENT)

#include "Spawner.h"
#include "MapBuilder.h"
#include "Ui.h"

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
		void awake() override {
			GameData* data = gameobject().getComponent<GameData>();
			data->numPlayers = nPlayers;
			data->playerInfos.resize(nPlayers);
		}

		void start() override {
			level = 1;

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
			invoke([=] {spawnLevel(level); }, 1.0f);
		}

		void spawnLevel(int level) {
			//disable ui text

			MapBuilder::instance()->buildLevel(level);
			Spawner::instance()->instantiatePlayers(GameData::instance()->numPlayers);
			Spawner::instance()->instantiateEnemies();
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