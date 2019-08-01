// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "../Engine.h"

#include "MapBuilder.h"
#include "CharacterManager.h"

// manages the game state and flow (PERSISTENT)

namespace sxg::boom {

	class GameManager : public Component {
	CLONABLE(GameManager)


	public:
		const int nPlayers = 1;
		const int startLevel = 25;

		static GameManager* instance() { return _instance; }

	private:
		// ________________________________ data
		static GameManager* _instance;



		// ________________________________ base
		void awake() override {
			if (_instance != nullptr) Debug::logError("Multiple copies of singleton: GameManager");
			_instance = this;
		}

		void start() override {
			//build static level
			MapBuilder* mapBuilder = gameobject().getComponent<MapBuilder>();
			mapBuilder->buildLevel(startLevel);

			//instantiate players
			CharacterManager::instance()->instantiatePlayers();

			//instantiate enemies
		}

		void update() override {

		}
		
		// ________________________________ commands
		void showHurryUp() {

		}

		void startExtraGame() {

		}

		void stopExtraGame() {

		}

		void levelComplete() {

		}

		void gameover() {

		}


		// ________________________________ queries



	};
}