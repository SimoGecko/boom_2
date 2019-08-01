// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "../Engine.h"

// __DESCRIPTION__

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
				GameObject::Instantiate("player", to_v2f(startPos["player"][i]));
			}
		}


		// ________________________________ queries



	};
}