// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "../Engine.h"

// instantiates right players and enemies
#include "MapBuilder.h"
#include "Player.h"
#include "GameManager.h"

namespace sxg::boom {

	class CharacterManager : public Component {
	CLONABLE(CharacterManager)
	public:
		static CharacterManager* instance() { return _instance; }


	private:
		// ________________________________ data

		friend class GameManager;
		static CharacterManager* _instance;

		// ________________________________ base
		void awake() override {
			if (_instance != nullptr) Debug::logError("Multiple copies of singleton: CharacterManager");
			_instance = this;
		}
		
		void start() override {
			Debug::log("xcall");
			//instantiatePlayers();
			//instantiateEnemies();
		}

		void update() override {

		}
		
		// ________________________________ commands
		void instantiatePlayers() {
			int numPlayers = GameManager::instance()->nPlayers;
			Debug::ensure(MapBuilder::instance()->playerStartPos.size() >= numPlayers, "Not enough player starting positions");
			for (int i = 0; i < numPlayers; ++i) {
				GameObject* playerGo = GameObject::Instantiate("player", to_v2f(MapBuilder::instance()->playerStartPos[i]));
				playerGo->getComponent<Player>()->setPlayerIndex(i);
			}
		}

		void instantiateEnemies() {
			//deal with which enemies go where
			for (sf::Vector2i pos : MapBuilder::instance()->enemyStartPos) {
				GameObject* enemy = GameObject::Instantiate("enemy", to_v2f(pos));

			}
		}


		// ________________________________ queries



	};
}