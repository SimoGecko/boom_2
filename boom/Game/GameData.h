// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "../Engine.h"

// manages PERSISTENT data for level, players (score/time/lives)

namespace sxg::boom {

	struct playerInfo {
		int lives;
		int halfHearts;
		int score;
		vector<bool> extra;

		playerInfo() : lives(3), halfHearts(16), score(0), extra(5, false) {}
	};

	class GameData : public Component {
	CLONABLE(GameData)
	public:
		static GameData* instance() { return _instance; }
		
		
		vector<playerInfo> playerInfos; // live here but player and UI get access to it
		int numPlayers;
		
	private:
		// ________________________________ data
		static GameData* _instance;




		// ________________________________ base
		void awake() override {
			if (_instance != nullptr) Debug::logError("Multiple copies of singleton: GameData");
			_instance = this;
		}
		
		void start() override {

		}

		void update() override {

		}




	};
}