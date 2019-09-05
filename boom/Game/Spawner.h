// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "../Engine.h"


#include "Player.h"
#include "Enemy.h"

// spawns the necessary stuff in the game

namespace sxg::boom {

	class Spawner : public Component {
	CLONABLE(Spawner)
	public:
		static Spawner* instance() { return _instance; }

	private:
		// ________________________________ data
		static Spawner* _instance;

		unordered_map<string, vector<sf::Vector2i>> startPos;
		friend class MapBuilder;
		friend class GameManager;

		// ________________________________ base
		void awake() {
			_instance = this;

		}

		void start() override {
		}

		void update() override {

		}
		
		// ________________________________ commands
		void instantiatePlayers(int numPlayers) {
			Debug::ensure(startPos["player"].size() >= numPlayers, "Not enough player starting positions");
			for (int i = 0; i < numPlayers; ++i) {
				//setup player
				GameObject* playerGo = GameObject::Instantiate("player", to_v2f(startPos["player"][i]));
				Player* player = playerGo->getComponent<Player>();
				player->setPlayerIdx(i);
			}
		}
		void instantiateEnemies() {
			for (sf::Vector2i pos : startPos["enemy"]) {
				GameObject::Instantiate("enemy", to_v2f(pos));
			}
		}


		// ________________________________ queries



	};
}